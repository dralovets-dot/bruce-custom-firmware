import os
import re

print("Проверка всех файлов на unsafe as< вызовы...")
print("=" * 60)

unsafe_files = []

for root, dirs, files in os.walk('src'):
    for file in files:
        if file.endswith(('.cpp', '.h')):
            filepath = os.path.join(root, file)
            
            with open(filepath, 'r') as f:
                content = f.read()
            
            # Ищем потенциально небезопасные вызовы as< без проверки is<
            lines = content.split('\n')
            unsafe_lines = []
            
            for i, line in enumerate(lines):
                if '.as<' in line:
                    # Проверяем что это безопасно (есть проверка is< или это to<JsonObject>)
                    line_safe = False
                    
                    # Проверяем предыдущие строки на наличие is< проверки
                    for j in range(max(0, i-3), i+1):
                        if 'is<' in lines[j] and '.as<' in line:
                            # Есть проверка в предыдущих строках
                            line_safe = True
                            break
                    
                    # to<JsonObject>() - это безопасно
                    if '.to<JsonObject>' in line:
                        line_safe = True
                    
                    # Тернарный оператор с проверкой
                    if '? ' in line and '.as<' in line and 'is<' in line:
                        line_safe = True
                    
                    if not line_safe:
                        unsafe_lines.append((i+1, line.strip()))
            
            if unsafe_lines:
                unsafe_files.append((filepath, unsafe_lines))

if unsafe_files:
    print("⚠️  Найдены потенциально небезопасные файлы:")
    for filepath, lines in unsafe_files:
        print(f"\n📄 {filepath}")
        for line_num, line_content in lines:
            print(f"   Строка {line_num}: {line_content}")
else:
    print("✅ Все файлы безопасны!")

print("=" * 60)
