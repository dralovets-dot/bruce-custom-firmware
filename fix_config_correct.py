with open('src/core/config.cpp', 'r') as f:
    content = f.read()

# Исправляем все проблемные места
import re

# 1. Исправляем &.as<JsonObject>() на doc.as<JsonObject>()
content = content.replace(
    'JsonObject root = doc.is<JsonObject>() ? &.as<JsonObject>() : JsonObject();',
    'JsonObject root = doc.is<JsonObject>() ? doc.as<JsonObject>() : JsonObject();'
)

# 2. Исправляем другие as<JsonObject>() вызовы
content = re.sub(
    r'JsonObject obj = configDoc\.as<JsonObject>\(\);',
    '''JsonObject obj;
    if (configDoc.is<JsonObject>()) {
        obj = configDoc.as<JsonObject>();
    }''',
    content
)

with open('src/core/config.cpp', 'w') as f:
    f.write(content)

print("config.cpp исправлен")
