import sys

with open('src/core/config.cpp', 'r') as f:
    content = f.read()

# Заменяем проблемную строку
new_content = content.replace(
    'JsonObject obj = configDoc.as<JsonObject>();',
    '''JsonObject obj;
    if (configDoc.is<JsonObject>()) {
        obj = configDoc.as<JsonObject>();
    }'''
)

with open('src/core/config.cpp', 'w') as f:
    f.write(new_content)

print("config.cpp исправлен")
