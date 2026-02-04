#!/bin/bash
FILE="src/modules/rf/rf_bruteforce.cpp"

# Создаем временный файл
cp "$FILE" "${FILE}.tmp"

# Используем awk чтобы переместить объявление max_keys перед cleanup секцией
awk '
/cleanup:/ {
    print "    uint32_t max_keys = (1u << bits);"
    print ""
}
{print}
' "$FILE" > "${FILE}.tmp"

# Удаляем старое объявление max_keys
sed -i '/uint32_t max_keys = (1u << bits);/d' "${FILE}.tmp"

# Проверяем что cleanup: есть
grep -n "cleanup:" "${FILE}.tmp"

mv "${FILE}.tmp" "$FILE"
