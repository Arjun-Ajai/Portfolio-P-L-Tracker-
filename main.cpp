#include <fstream>
#include <iostream>

#include "portfolio.h"

int main() {
    std::cout << "Portfolio P&L Tracker\n";
    std::cout << "----------------------\n";

    Portfolio portfolio;
    std::ifstream existing_trades("trades.csv");
    if (existing_trades.good()) {
        portfolio.load();
        std::cout << "Loaded existing trade history.\n";
    } else {
        std::cout << "No saved trades found. Starting with an empty portfolio.\n";
    }

    return 0;
}
