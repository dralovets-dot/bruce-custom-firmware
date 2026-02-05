import re

with open('src/core/config.cpp', 'r') as f:
    content = f.read()

print("Ищем проблемные строки...")

# Находим ВСЕ проблемные места
problem_lines = []
for i, line in enumerate(content.split('\n'), 1):
    if '&.as<JsonObject>()' in line:
        print(f"Строка {i}: {line.strip()}")
        problem_lines.append(i)
    if 'JsonObject obj = configDoc.as<JsonObject>()' in line and 'if' not in line:
        print(f"Строка {i}: {line.strip()}")
        problem_lines.append(i)

# Исправляем
if problem_lines:
    lines = content.split('\n')
    for i in problem_lines:
        idx = i-1
        if '&.as<JsonObject>()' in lines[idx]:
            lines[idx] = lines[idx].replace('&.as<JsonObject>()', 'doc.as<JsonObject>()')
            print(f"Исправлена строка {i}: {lines[idx]}")
        elif 'JsonObject obj = configDoc.as<JsonObject>()' in lines[idx]:
            # Находим отступ
            indent = len(lines[idx]) - len(lines[idx].lstrip())
            spaces = ' ' * indent
            lines[idx] = f"{spaces}JsonObject obj;\n{spaces}if (configDoc.is<JsonObject>()) {{\n{spaces}    obj = configDoc.as<JsonObject>();\n{spaces}}}"
            print(f"Исправлена строка {i}")
    
    with open('src/core/config.cpp', 'w') as f:
        f.write('\n'.join(lines))
    print("✅ config.cpp исправлен")
else:
    print("❌ Проблемные строки не найдены, проверьте файл")
