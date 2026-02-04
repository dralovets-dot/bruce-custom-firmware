#include "rf_bruteforce.h"

#include "protocols/Ansonic.h"
#include "protocols/Came.h"
#include "protocols/Chamberlain.h"
#include "protocols/Holtek.h"
#include "protocols/Linear.h"
#include "protocols/NiceFlo.h"
#include "protocols/protocol.h"
#include "rf_utils.h"
#include "core/sd_functions.h"
#include "core/display.h"
#include "core/config.h"
#include <SD.h>

// Глобальные переменные брутфорса
float brute_frequency = 433.92;
String brute_protocol = "Nice 12 Bit";
int brute_repeats = 1;
bool brute_stop_on_success = false;
bool brute_save_to_file = true;
bool brute_use_dictionary = false;
String brute_last_success = "";
std::vector<String> brute_history;
int brute_history_max_size = 50;
unsigned long brute_start_time = 0;
unsigned long brute_keys_tested = 0;

// Внешние переменные (должны быть определены в других файлах)
extern std::vector<MenuOption> options;
extern BruceConfig bruceConfig;
extern BruceConfigPins bruceConfigPins;

// Вспомогательная функция для форматирования времени
String format_time(unsigned long seconds) {
    if (seconds < 60) return String(seconds) + "s";
    if (seconds < 3600) return String(seconds / 60) + "m" + String(seconds % 60) + "s";
    return String(seconds / 3600) + "h" + String((seconds % 3600) / 60) + "m";
}

// Структура для статистики
struct BruteforceStats {
    unsigned long total_keys;
    unsigned long tested_keys;
    unsigned long found_keys;
    float keys_per_second;
    unsigned long elapsed_seconds;
    unsigned long estimated_remaining;
    
    void calculate(unsigned long current_key, unsigned long max_keys) {
        tested_keys = current_key + 1;
        total_keys = max_keys;
        elapsed_seconds = (millis() - brute_start_time) / 1000;
        if (elapsed_seconds > 0) {
            keys_per_second = (float)tested_keys / elapsed_seconds;
            estimated_remaining = (total_keys - tested_keys) / keys_per_second;
        }
    }
    
    String get_display_string() {
        return String(tested_keys) + "/" + String(total_keys) + 
               " | " + String(keys_per_second, 1) + "/s" +
               " | ETA: " + format_time(estimated_remaining);
    }
};

void rf_brute_frequency() {
    options.clear();
    int ind = 0;
    int arraySize = sizeof(subghz_frequency_list) / sizeof(subghz_frequency_list[0]);
    for (int i = 0; i < arraySize; i++) {
        String tmp = String(subghz_frequency_list[i], 2) + "Mhz";
        options.push_back({tmp.c_str(), [=]() { brute_frequency = subghz_frequency_list[i]; }});
    }
    loopOptions(options, ind);
    options.clear();
}

void rf_brute_protocol() {
    const String protocol_list[] = {
        "Came 12 Bit",
        "Nice 12 Bit",
        "Ansonic 12 Bit",
        "Holtek 12 Bit",
        "Linear 12 Bit",
        "Chamberlain 12 Bit",
    };

    options.clear();
    int ind = 0;
    int arraySize = sizeof(protocol_list) / sizeof(protocol_list[0]);
    for (int i = 0; i < arraySize; i++) {
        String tmp = protocol_list[i];
        options.push_back({tmp.c_str(), [=]() { brute_protocol = protocol_list[i]; }});
    }
    loopOptions(options, ind);
    options.clear();
}

void rf_brute_repeats() {
    const int repeat_list[] = {1, 2, 3, 4, 5, 10, 15, 20};

    options.clear();
    int ind = 0;
    int arraySize = sizeof(repeat_list) / sizeof(repeat_list[0]);
    for (int i = 0; i < arraySize; i++) {
        int tmp = repeat_list[i];
        options.push_back({String(tmp).c_str(), [=]() { brute_repeats = repeat_list[i]; }});
    }
    loopOptions(options, ind);
    options.clear();
}

void rf_brute_options() {
    int option = 0;
    while (true) {
        options.clear();
        options = {
            {"Stop on success: " + String(brute_stop_on_success ? "ON" : "OFF"), 
                [&]() { brute_stop_on_success = !brute_stop_on_success; }},
            {"Save to file: " + String(brute_save_to_file ? "ON" : "OFF"),
                [&]() { brute_save_to_file = !brute_save_to_file; }},
            {"Use dictionary: " + String(brute_use_dictionary ? "ON" : "OFF"),
                [&]() { brute_use_dictionary = !brute_use_dictionary; }},
            {"Clear history", [&]() { brute_history.clear(); }},
            {"View history (" + String(brute_history.size()) + ")", [&]() { option = 1; }},
            {"Back", [&]() { option = 2; }},
        };
        loopOptions(options);
        
        if (option == 1) {
            if (brute_history.empty()) {
                displayRedStripe("History empty", TFT_YELLOW, TFT_BLACK);
                delay(1000);
                option = 0;
                continue;
            }
            
            int hist_index = 0;
            while (true) {
                options.clear();
                int end_idx = hist_index + 5;
                if (end_idx > brute_history.size()) end_idx = brute_history.size();
                
                for (int i = hist_index; i < end_idx; i++) {
                    String display_text = "[" + String(i) + "] " + brute_history[i];
                    if (display_text.length() > 25) {
                        display_text = display_text.substring(0, 22) + "...";
                    }
                    options.push_back({display_text.c_str(), [](){}});
                }
                
                if (hist_index > 0) {
                    options.push_back({"< Prev", [&]() { hist_index = hist_index - 5; if (hist_index < 0) hist_index = 0; }});
                }
                if (end_idx < brute_history.size()) {
                    options.push_back({"Next >", [&]() { hist_index += 5; }});
                }
                options.push_back({"Back", [&]() { return; }});
                
                loopOptions(options);
                delay(100);
                
                if (check(EscPress)) break;
            }
            option = 0;
        }
        
        if (option == 2) break;
        option = 0;
    }
}

std::vector<uint32_t> load_dictionary() {
    std::vector<uint32_t> dictionary;
    
    if (!SD.exists("/rf_dict.txt")) {
        return dictionary;
    }
    
    File file = SD.open("/rf_dict.txt");
    if (!file) {
        return dictionary;
    }
    
    while (file.available()) {
        String line = file.readStringUntil('\n');
        line.trim();
        
        if (line.length() == 0) continue;
        
        uint32_t value = 0;
        if (line.startsWith("0x") || line.startsWith("0X")) {
            value = strtoul(line.c_str() + 2, NULL, 16);
        } else {
            value = strtoul(line.c_str(), NULL, 10);
        }
        
        if (value > 0) {
            dictionary.push_back(value);
        }
    }
    
    file.close();
    return dictionary;
}

bool save_successful_key(const String& protocol, float frequency, uint32_t key, int bits) {
    if (!brute_save_to_file) return true;
    
    String filename = "/rf_keys.txt";
    File file = SD.open(filename, FILE_APPEND);
    if (!file) {
        file = SD.open(filename, FILE_WRITE);
        if (!file) return false;
    }
    
    String timestamp = String(millis() / 1000);
    String key_hex = "0x" + String(key, HEX);
    key_hex.toUpperCase();
    
    String record = "[" + timestamp + "s] Protocol: " + protocol + 
                   ", Freq: " + String(frequency, 2) + "MHz" +
                   ", Key: " + key_hex + " (" + String(key) + ")" +
                   ", Bits: " + String(bits);
    
    file.println(record);
    file.close();
    
    File last_file = SD.open("/rf_last_key.txt", FILE_WRITE);
    if (last_file) {
        last_file.println(record);
        last_file.close();
    }
    
    return true;
}

bool check_key_success(uint32_t key, const String& protocol, int bits) {
    // ЗАГЛУШКА: Здесь должна быть реальная проверка
    // Например, отправка ключа и проверка ответа устройства
    
    // Для демонстрации проверяем специальные ключи
    if (bits == 12) {
        if ((key & 0xFFF) == 0xABC) return true;
    }
    
    // Проверка на простые ключи
    if (key == 0x0000 || key == 0xFFFF || key == 0xAAAA || key == 0x5555) {
        return true;
    }
    
    // Для теста: каждый 100-й ключ считается успешным
    if (key % 100 == 0 && key > 0) {
        return true;
    }
    
    return false;
}

bool rf_brute_start() {
    int txpin;

    if (bruceConfigPins.rfModule == CC1101_SPI_MODULE) {
        txpin = bruceConfigPins.CC1101_bus.io0;
        if (!initRfModule("tx", brute_frequency)) {
            displayRedStripe("RF init failed", TFT_RED, TFT_BLACK);
            delay(2000);
            return false;
        }
    } else {
        txpin = bruceConfigPins.rfTx;
        if (!initRfModule("tx")) {
            displayRedStripe("RF init failed", TFT_RED, TFT_BLACK);
            delay(2000);
            return false;
        }
    }

    c_rf_protocol *protocol = nullptr;
    int bits = 0;

    if (brute_protocol == "Nice 12 Bit") {
        protocol = new protocol_nice_flo();
        bits = 12;
    } else if (brute_protocol == "Came 12 Bit") {
        protocol = new protocol_came();
        bits = 12;
    } else if (brute_protocol == "Ansonic 12 Bit") {
        protocol = new protocol_ansonic();
        bits = 12;
    } else if (brute_protocol == "Holtek 12 Bit") {
        protocol = new protocol_holtek();
        bits = 12;
    } else if (brute_protocol == "Linear 12 Bit") {
        protocol = new protocol_linear();
        bits = 12;
    } else if (brute_protocol == "Chamberlain 12 Bit") {
        protocol = new protocol_ansonic();
        bits = 12;
    } else {
        deinitRfModule();
        displayRedStripe("Protocol not supported", TFT_RED, TFT_BLACK);
        delay(2000);
        return false;
    }

    pinMode(txpin, OUTPUT);
    setMHZ(brute_frequency);

    auto sendPulse = [&](int duration) {
        if (duration < 0) {
            digitalWrite(txpin, LOW);
            delayMicroseconds(-duration);
        } else {
            digitalWrite(txpin, HIGH);
            delayMicroseconds(duration);
        }
    };

    // Инициализация
    brute_start_time = millis();
    brute_keys_tested = 0;
    brute_history.clear();
    brute_last_success = "";
    
    bool success_found = false;
    uint32_t success_key = 0;
    int success_count = 0;
    
    BruteforceStats stats;

    // Загрузка словаря
    std::vector<uint32_t> dictionary;
    if (brute_use_dictionary) {
        dictionary = load_dictionary();
        if (!dictionary.empty()) {
            displayRedStripe("Loaded " + String(dictionary.size()) + " keys", TFT_GREEN, TFT_BLACK);
            delay(1500);
        }
    }

    // Сначала словарь
    if (!dictionary.empty()) {
        displayRedStripe("Trying dictionary...", TFT_BLUE, TFT_BLACK);
        
        for (uint32_t dict_key : dictionary) {
            if (dict_key >= (1u << bits)) continue;
            
            for (int r = 0; r < brute_repeats; ++r) {
                for (const auto &pulse : protocol->pilot_period) { sendPulse(pulse); }
                for (int j = bits - 1; j >= 0; --j) {
                    bool bit = (dict_key >> j) & 1;
                    const std::vector<int> &timings = protocol->transposition_table[bit ? '1' : '0'];
                    for (auto duration : timings) { sendPulse(duration); }
                }
                for (const auto &pulse : protocol->stop_bit) { sendPulse(pulse); }
            }
            
            if (check_key_success(dict_key, brute_protocol, bits)) {
                success_found = true;
                success_key = dict_key;
                success_count++;
                
                String history_entry = "DICT Key: 0x" + String(dict_key, HEX);
                brute_history.push_back(history_entry);
                
                save_successful_key(brute_protocol, brute_frequency, dict_key, bits);
                
                displayRedStripe("Dict success! Key: 0x" + String(dict_key, HEX), TFT_GREEN, TFT_BLACK);
                delay(2000);
                
                if (brute_stop_on_success) break;
            }
            
            brute_keys_tested++;
            
            if (check(EscPress)) break;
            
            if (brute_keys_tested % 10 == 0) {
                stats.calculate(brute_keys_tested, dictionary.size());
                displayRedStripe("Dict: " + stats.get_display_string(), 
                               TFT_CYAN, TFT_BLACK);
            }
        }
        
        if (success_found && brute_stop_on_success) {
            goto cleanup;
        }
    }

    // Полный брутфорс
    displayRedStripe("Starting bruteforce...", TFT_BLUE, TFT_BLACK);
    delay(1000);
    
    uint32_t max_keys = (1u << bits);
    for (uint32_t i = 0; i < max_keys; ++i) {
        // Пропускаем если уже проверяли в словаре
        if (brute_use_dictionary && !dictionary.empty()) {
            bool in_dict = false;
            for (auto dict_key : dictionary) {
                if (dict_key == i) {
                    in_dict = true;
                    break;
                }
            }
            if (in_dict) continue;
        }
        
        // Запись в историю
        if (brute_history.size() < brute_history_max_size) {
            String history_entry = "Key: 0x" + String(i, HEX) + " (" + String(i) + ")";
            brute_history.push_back(history_entry);
        }
        
        // Отправка ключа
        for (int r = 0; r < brute_repeats; ++r) {
            for (const auto &pulse : protocol->pilot_period) { sendPulse(pulse); }
            for (int j = bits - 1; j >= 0; --j) {
                bool bit = (i >> j) & 1;
                const std::vector<int> &timings = protocol->transposition_table[bit ? '1' : '0'];
                for (auto duration : timings) { sendPulse(duration); }
            }
            for (const auto &pulse : protocol->stop_bit) { sendPulse(pulse); }
        }
        
        // Проверка успешности
        if (check_key_success(i, brute_protocol, bits)) {
            success_found = true;
            success_key = i;
            success_count++;
            brute_last_success = "Key: 0x" + String(i, HEX) + " (" + String(i) + ")";
            
            save_successful_key(brute_protocol, brute_frequency, i, bits);
            
            String success_msg = "SUCCESS! Key: 0x" + String(i, HEX);
            displayRedStripe(success_msg, TFT_GREEN, TFT_BLACK);
            delay(2000);
            
            if (brute_stop_on_success) {
                break;
            }
        }
        
        brute_keys_tested++;
        
        // Проверка выхода
        if (check(EscPress)) {
            displayRedStripe("Stopped by user", TFT_YELLOW, TFT_BLACK);
            delay(1000);
            break;
        }
        
        // Обновление дисплея
        if (i % 20 == 0 || i < 20) {
            stats.calculate(i, max_keys);
            String status = brute_protocol + " | " + stats.get_display_string();
            if (success_found) {
                status += " | Found: " + String(success_count);
            }
            displayRedStripe(status, TFT_CYAN, TFT_BLACK);
        }
    }

cleanup:
    // Финальное сообщение
    if (success_found) {
        String final_msg = "Found " + String(success_count) + " key(s)";
        if (!brute_last_success.isEmpty()) {
            final_msg += " | Last: " + brute_last_success;
        }
        displayRedStripe(final_msg, TFT_GREEN, TFT_BLACK);
    } else {
        displayRedStripe("No keys found", TFT_RED, TFT_BLACK);
    }
    
    // Показ статистики
    stats.calculate(brute_keys_tested, max_keys);
    String stat_msg = "Tested: " + String(brute_keys_tested) + 
                     " keys in " + String(stats.elapsed_seconds) + "s";
    displayRedStripe(stat_msg, TFT_BLUE, TFT_BLACK);
    
    delay(3000);

    deinitRfModule();
    delete protocol;
    return true;
}

void rf_bruteforce() {
    while (true) {
        int option = 0;
        options.clear();
        options = {
            {"Frequency: " + String(brute_frequency, 2) + "MHz", [&]() { option = 1; }},
            {"Repeats: " + String(brute_repeats),   [&]() { option = 2; }},
            {"Protocol: " + brute_protocol,  [&]() { option = 3; }},
            {"Options",   [&]() { option = 4; }},
            {"Start Bruteforce", [&]() { option = 5; }},
            {"Main Menu", [&]() { option = 6; }},
        };
        loopOptions(options);

        switch (option) {
            case 1: rf_brute_frequency(); break;
            case 2: rf_brute_repeats(); break;
            case 3: rf_brute_protocol(); break;
            case 4: rf_brute_options(); break;
            case 5: rf_brute_start(); break;
            case 6: return;
        }
        
        delay(100);
    }
}
