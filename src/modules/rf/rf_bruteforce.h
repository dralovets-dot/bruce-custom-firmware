#pragma once

#include <Arduino.h>
#include <vector>

// Основные функции брутфорса
void rf_bruteforce();
void rf_brute_frequency();
void rf_brute_protocol();
void rf_brute_repeats();
void rf_brute_options();
bool rf_brute_start();

// Вспомогательные функции
String format_time(unsigned long seconds);
bool save_successful_key(const String& protocol, float frequency, uint32_t key, int bits);
bool check_key_success(uint32_t key, const String& protocol, int bits);
std::vector<uint32_t> load_dictionary();

// Глобальные переменные (extern для доступа из других модулей при необходимости)
extern float brute_frequency;
extern String brute_protocol;
extern int brute_repeats;
extern bool brute_stop_on_success;
extern bool brute_save_to_file;
extern bool brute_use_dictionary;
extern String brute_last_success;
extern std::vector<String> brute_history;
extern int brute_history_max_size;
extern unsigned long brute_start_time;
extern unsigned long brute_keys_tested;
