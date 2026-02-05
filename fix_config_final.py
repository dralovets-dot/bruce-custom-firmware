with open('src/core/config.cpp', 'r') as f:
    lines = f.readlines()

for i in range(len(lines)):
    if '&.as<JsonObject>()' in lines[i]:
        lines[i] = lines[i].replace('&.as<JsonObject>()', 'doc.as<JsonObject>()')
        print(f"Исправлена строка {i+1}")

with open('src/core/config.cpp', 'w') as f:
    f.writelines(lines)
print("config.cpp исправлен")
