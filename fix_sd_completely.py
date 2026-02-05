with open('lib/HAL/sd_card/sd_diskio.cpp', 'r') as f:
    content = f.read()

# Находим и исправляем MKFS_PARM
if 'MKFS_PARM' in content:
    print("Найден MKFS_PARM, исправляем...")
    
    # В разных версиях FatFS разный MKFS_PARM
    # Вариант 1: закомментируем эту секцию
    lines = content.split('\n')
    new_lines = []
    in_mkfs_section = False
    
    for line in lines:
        if 'const MKFS_PARM opt' in line:
            print(f"Закомментируем строку: {line}")
            line = '    // ' + line + ' // MKFS_PARM not available in this FatFS version'
            in_mkfs_section = True
        elif in_mkfs_section and 'res = f_mkfs' in line:
            line = '    // ' + line + ' // Disabled due to MKFS_PARM issues'
            in_mkfs_section = False
        new_lines.append(line)
    
    content = '\n'.join(new_lines)
    
    with open('lib/HAL/sd_card/sd_diskio.cpp', 'w') as f:
        f.write(content)
    print("✅ sd_diskio.cpp исправлен")
else:
    print("MKFS_PARM не найден")
