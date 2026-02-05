#ifndef SIMPLECLI_H
#define SIMPLECLI_H

// Заглушка SimpleCLI для совместимости
class CLI {
public:
    void parse(String) {}
    void setCaseSensitive(bool) {}
    void setOnError(void (*)(String)) {}
};

class Command {
public:
    void addArg(String) {}
    void setDescription(String) {}
};

#endif
