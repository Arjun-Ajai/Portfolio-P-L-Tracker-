#include "portfolio.h"
#include <fstream>
#include <sstream>
#include <iostream>

void Portfolio::add_trade_silent(const Trade& t) {
    trade.push_back(t);

    if (t.side == "BUY") {
        double old_qty = net_qty[t.symbol];
        double old_avg = avg_cost[t.symbol];
        net_qty[t.symbol] = old_qty + t.quantity;
        avg_cost[t.symbol] = (old_avg * old_qty + t.price * t.quantity) / net_qty[t.symbol];
    }
    else if (t.side == "SELL") {
        double old_qty = net_qty[t.symbol];
        net_qty[t.symbol] = old_qty - t.quantity;
        double old_avg = avg_cost[t.symbol];

        if (net_qty[t.symbol] <= 0.0) {
            avg_cost[t.symbol] = 0.0;
        }
        realized[t.symbol] += (t.price - old_avg) * t.quantity;
    }
}

void Portfolio::add_trade(const Trade& t) {
    add_trade_silent(t);
    save();
}

void Portfolio::save() {
    std::ofstream file("trades.csv");
    if (!file.is_open()) {
        std::cerr << "Can't open the file!\n";
        return;
    }

    file << "symbol|side|quantity|price|timestamp|source\n";
    for (const auto& t : trade) {
        file << t.to_csv() << "\n";
    }
}

void Portfolio::load() {
    std::ifstream file("trades.csv");
    if (!file.is_open()) {
        return;
    }

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        Trade t;
        std::stringstream ss(line);
        std::string token;
        int column = 0;

        while (std::getline(ss, token, '|')) {
            switch (column) {
                case 0: t.symbol = token; break;
                case 1: t.side = token; break;
                case 2: t.quantity = std::stod(token); break;
                case 3: t.price = std::stod(token); break;
                case 4: t.timestamp = token; break;
                case 5: t.source = token; break;
                default: break;
            }
            column++;
        }
        add_trade_silent(t);
    }
}

void Portfolio::print_history() const {
    std::cout << "--- TRADE HISTORY ---\n";
    if (trade.empty()) {
        std::cout << "No trades recorded.\n";
        return;
    }

    for (const auto& t : trade) {
        std::cout << t.symbol << " | " << t.side
                  << " | Qty: " << t.quantity
                  << " | Price: $" << t.price
                  << " | Time: " << t.timestamp
                  << " | Source: " << t.source << "\n";
    }
}

void Portfolio::print_positions(double current_price) const {
    std::cout << "--- OPEN POSITIONS ---\n";
    for (const auto& pair : net_qty) {
        const std::string& symbol = pair.first;
        double qty = pair.second;

        if (qty == 0.0) {
            continue;
        }

        double cost = avg_cost.at(symbol);
        double unrealized_pnl = (current_price - cost) * qty;

        std::cout << "Symbol: " << symbol
                  << " | Qty: " << qty
                  << " | Avg Cost: $" << cost
                  << " | Market Price: $" << current_price
                  << " | Unrealized P&L: $" << unrealized_pnl << "\n";
    }
}

void Portfolio::print_pnl() const {
    std::cout << "--- REALIZED P&L ---\n";
    if (realized.empty()) {
        std::cout << "No realized P&L yet.\n";
        return;
    }

    for (const auto& [symbol, pnl] : realized) {
        std::cout << symbol << " | Realized P&L: $" << pnl << "\n";
    }
}