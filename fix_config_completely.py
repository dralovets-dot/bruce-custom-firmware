import re

with open('src/core/config.cpp', 'r') as f:
    content = f.read()

print("Ищем ВСЕ проблемные места...")

# 1. Находим ВСЕ вызовы configDoc.as<JsonObject>()
lines = content.split('\n')
changes = []

for i, line in enumerate(lines):
    # Ищем configDoc.as<JsonObject>() без проверки
    if 'configDoc.as<JsonObject>()' in line and 'if' not in line and '?' not in line:
        print(f"Найдена проблемная строка {i+1}: {line.strip()}")
        
        # Определяем отступ
        indent = len(line) - len(line.lstrip())
        spaces = ' ' * indent
        
        # Заменяем на безопасную версию
        lines[i] = f"{spaces}JsonObject obj;\n{spaces}if (configDoc.is<JsonObject>()) {{\n{spaces}    obj = configDoc.as<JsonObject>();\n{spaces}}}"
        changes.append(f"Строка {i+1}")
    
    # Также проверяем другие потенциальные проблемы
    elif 'doc.as<JsonObject>()' in line and 'if' not in line and '?' not in line:
        print(f"Возможная проблема в строке {i+1}: {line.strip()}")
        
        # Проверяем что это не часть безопасной конструкции
        if not ('is<JsonObject>()' in lines[i-1] if i > 0 else False):
            indent = len(line) - len(line.lstrip())
            spaces = ' ' * indent
            
            # Извлекаем имя переменной
            match = re.match(r'\s*JsonObject\s+(\w+)\s*=\s*(\w+)\.as<JsonObject>', line)
            if match:
                var_name = match.group(1)
                doc_name = match.group(2)
                lines[i] = f"{spaces}JsonObject {var_name};\n{spaces}if ({doc_name}.is<JsonObject>()) {{\n{spaces}    {var_name} = {doc_name}.as<JsonObject>();\n{spaces}}}"
                changes.append(f"Строка {i+1} (другая)")

if changes:
    with open('src/core/config.cpp', 'w') as f:
        f.write('\n'.join(lines))
    print(f"\n✅ Исправлены строки: {', '.join(changes)}")
else:
    print("\n⚠️ Проблемные строки не найдены, создаем безопасную версию...")
    # Создаем полностью безопасную версию
    safe_content = content
    safe_content = re.sub(
        r'JsonObject obj = configDoc\.as<JsonObject>\(\);',
        'JsonObject obj;\n    if (configDoc.is<JsonObject>()) {\n        obj = configDoc.as<JsonObject>();\n    }',
        safe_content
    )
    
    with open('src/core/config.cpp', 'w') as f:
        f.write(safe_content)
    print("✅ Создана безопасная версия")
