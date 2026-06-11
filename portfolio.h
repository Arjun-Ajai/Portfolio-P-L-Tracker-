#pragma once
#include <vector>
#include "trade.h"
#include <map>
class Portfolio{
private:
    std::vector<Trade> trade;
    std::map<std::string,double> net_qty;
    std::map<std::string,double> avd_cost;
    std::map<std::string,double> realized;
public:
    void add_trade();
    void save();
    void load();
    void print_positions();
    void print_history();
    void print_pnl();

    Portfolio();
};