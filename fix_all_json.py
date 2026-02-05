import os
import re

def fix_file(filepath):
    with open(filepath, 'r') as f:
        content = f.read()
    
    original = content
    changes = []
    
    # 1. Исправляем &.as<JsonObject>() на proper.as<JsonObject>()
    if '&.as<JsonObject>()' in content:
        # Находим имя переменной перед точкой
        lines = content.split('\n')
        for i, line in enumerate(lines):
            if '&.as<JsonObject>()' in line:
                # Ищем переменную в предыдущих строках
                for j in range(i, max(-1, i-5), -1):
                    if '=' in lines[j] and 'JsonObject' in lines[j]:
                        match = re.search(r'(\w+)\s*=', lines[j])
                        if match:
                            var_name = match.group(1)
                            lines[i] = lines[i].replace('&.as<JsonObject>()', f'{var_name}.as<JsonObject>()')
                            changes.append(f"Строка {i+1}: &.as<JsonObject>() -> {var_name}.as<JsonObject>()")
                            break
        
        content = '\n'.join(lines)
    
    # 2. Исправляем JsonDocument var; на DynamicJsonDocument var(size);
    lines = content.split('\n')
    for i, line in enumerate(lines):
        match = re.match(r'(\s*)JsonDocument\s+(\w+)\s*;', line)
        if match:
            indent = match.group(1)
            var_name = match.group(2)
            lines[i] = f"{indent}DynamicJsonDocument {var_name}(1024);"
            changes.append(f"Строка {i+1}: JsonDocument -> DynamicJsonDocument")
    
    content = '\n'.join(lines)
    
    # 3. Исправляем другие проблемные as<...> вызовы
    # Паттерн: something = doc.as<JsonObject>();
    content = re.sub(
        r'(\w+)\s*=\s*(\w+)\.as<JsonObject>\(\);',
        r'\1;\n    if (\2.is<JsonObject>()) {\n        \1 = \2.as<JsonObject>();\n    }',
        content
    )
    
    if content != original:
        with open(filepath, 'w') as f:
            f.write(content)
        return changes
    return []

# Находим все C++ файлы
cpp_files = []
for root, dirs, files in os.walk('src'):
    for file in files:
        if file.endswith(('.cpp', '.h', '.ino')):
            cpp_files.append(os.path.join(root, file))

total_changes = 0
for file in cpp_files:
    changes = fix_file(file)
    if changes:
        print(f"\n📄 {file}")
        for change in changes:
            print(f"  {change}")
        total_changes += len(changes)

print(f"\n✅ Исправлено {total_changes} проблем в {len([f for f in cpp_files if fix_file(f)])} файлах")
