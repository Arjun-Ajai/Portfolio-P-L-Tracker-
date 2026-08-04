#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include "portfolio.h"

std::string get_timestamp() {
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y-%m-%dT%H:%M:%S");
    return ss.str();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./portfolio <command> [args]\n";
        std::cout << "Commands:\n";
        std::cout << "  add <BUY|SELL> <SYMBOL> <QTY> <PRICE>\n";
        std::cout << "  positions <MARKET_PRICE>\n";
        std::cout << "  history\n";
        std::cout << "  pnl\n";
        return 1;
    }

    Portfolio portfolio;
    portfolio.load();

    std::string cmd(argv[1]);

    if (cmd == "add") {
        if (argc < 6) {
            std::cerr << "Error: Usage: ./portfolio add <BUY|SELL> <SYMBOL> <QTY> <PRICE>\n";
            return 1;
        }

        Trade t;
        t.side = std::string(argv[2]);
        t.symbol = std::string(argv[3]);

        for (auto& c : t.side) c = toupper(c);
        for (auto& c : t.symbol) c = toupper(c);

        if (t.side != "BUY" && t.side != "SELL") {
            std::cerr << "Error: side must be BUY or SELL\n";
            return 1;
        }

        try {
            t.quantity = std::stod(argv[4]);
            t.price = std::stod(argv[5]);
        } catch (const std::invalid_argument&) {
            std::cerr << "Error: quantity and price must be numbers\n";
            return 1;
        } catch (const std::out_of_range&) {
            std::cerr << "Error: numerical input out of range\n";
            return 1;
        }

        if (t.quantity <= 0 || t.price <= 0) {
            std::cerr << "Error: quantity and price must be positive\n";
            return 1;
        }

        t.timestamp = get_timestamp();
        t.source = "MANUAL";

        portfolio.add_trade(t);
        std::cout << "Trade recorded successfully.\n";
    }
    else if (cmd == "positions") {
        if (argc < 3) {
            std::cerr << "Error: Usage: ./portfolio positions <MARKET_PRICE>\n";
            return 1;
        }
        try {
            double price = std::stod(argv[2]);
            portfolio.print_positions(price);
        } catch (const std::invalid_argument&) {
            std::cerr << "Error: market price must be a valid number\n";
            return 1;
        }
    }
    else if (cmd == "history") {
        portfolio.print_history();
    }
    else if (cmd == "pnl") {
        portfolio.print_pnl();
    }
    else {
        std::cerr << "Error: Unknown command '" << cmd << "'\n";
        return 1;
    }

    return 0;
}