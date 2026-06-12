#pragma once
#include <vector>
#include "trade.h"
#include <map>
class Portfolio{
private:
    std::vector<Trade> trade;
    std::map<std::string,double> net_qty;
    std::map<std::string,double> avg_cost;
    std::map<std::string,double> realized;
public:
    void add_trade(const Trade& t);
    void save();
    void load();
    void print_positions(double current_price);
    void print_history();
    void print_pnl();

    Portfolio();
};