#!/bin/bash
echo "Универсальное исправление ArduinoJson проблем..."

# 1. Заменяем ВСЕ &.as< на правильные вызовы
# Находим контекст и исправляем
for file in $(find src -name "*.cpp" -o -name "*.h"); do
    if grep -q "&\.as<" "$file"; then
        echo "Исправляем $file"
        # Временное исправление - просто убираем &
        sed -i 's/&\.as</.as</g' "$file"
    fi
done

# 2. Заменяем JsonDocument на DynamicJsonDocument
for file in $(find src -name "*.cpp" -o -name "*.h"); do
    if grep -q "JsonDocument [a-zA-Z_]" "$file" && ! grep -q "DynamicJsonDocument" "$file"; then
        echo "Обновляем JsonDocument в $file"
        sed -i 's/JsonDocument \([a-zA-Z_][a-zA-Z0-9_]*\);/DynamicJsonDocument \1(1024);/g' "$file"
    fi
done

echo "✅ Универсальные исправления применены"
