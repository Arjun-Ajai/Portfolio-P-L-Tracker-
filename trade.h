#pragma once
#include <string>

struct Trade {
    std::string symbol;
    std::string side;
    double quantity;
    double price;
    std::string timestamp;
    std::string source;

    std::string to_csv() const {
        return symbol + "|" + side + "|" + std::to_string(quantity) + "|" + std::to_string(price) + "|" + timestamp +
               "|" + source;
    }
};
