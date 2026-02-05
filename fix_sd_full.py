with open('lib/HAL/sd_card/sd_diskio.cpp', 'r') as f:
    content = f.read()

lines = content.split('\n')
new_lines = []
for line in lines:
    # Исправляем perimanSetPinBusExtraType
    if 'perimanSetPinBusExtraType' in line:
        line = '    // ' + line + ' // Commented for compatibility'
    
    # Исправляем MKFS_PARM
    if 'const MKFS_PARM opt = {' in line:
        line = '    const MKFS_PARM opt = {(BYTE)FM_ANY, 0, 0, 0}; // Updated for FatFS'
    
    new_lines.append(line)

with open('lib/HAL/sd_card/sd_diskio.cpp', 'w') as f:
    f.write('\n'.join(new_lines))

print("sd_diskio.cpp исправлен")
