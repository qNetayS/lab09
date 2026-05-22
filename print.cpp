#include "print.h"

std::string print(const std::string& message) {
    return "[" + message + "]";
}

void print(std::ostream& os, const std::string& message) {
    os << "[" << message << "]";
}
