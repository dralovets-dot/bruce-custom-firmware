#ifndef ESP32_HAL_PERIMAN_H
#define ESP32_HAL_PERIMAN_H

// Заглушка для совместимости
#ifdef __cplusplus
extern "C" {
#endif

// Пустые заглушки функций
void perimanClearPinBus(uint8_t pin);
bool perimanSetPinBus(uint8_t pin, uint32_t type, void * bus);
void* perimanGetPinBus(uint8_t pin, uint32_t type);

#ifdef __cplusplus
}
#endif

#endif // ESP32_HAL_PERIMAN_H