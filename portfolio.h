#pragma once
#include <vector>
#include <map>
#include <string>
#include "trade.h"

class Portfolio {
private:
    std::vector<Trade> trade;
    std::map<std::string, double> net_qty;
    std::map<std::string, double> avg_cost;
    std::map<std::string, double> realized;

    void add_trade_silent(const Trade& t);

public:
    void add_trade(const Trade& t);
    void save();
    void load();
    void print_positions(double current_price) const;
    void print_history() const;
    void print_pnl() const;

    Portfolio() = default;
};