#include "portfolio.h"
#include "trade.h"
#include <fstream>
#include <sstream>
#include <iostream>

    void Portfolio::add_trade(const Trade& t){
        trade.push_back(t);
        if(t.side=="BUY"){
            double old_qty=net_qty[t.symbol];
            net_qty[t.symbol]=old_qty+t.quantity;
            double old_avg=avg_cost[t.symbol];
            avg_cost[t.symbol]=((old_avg*old_qty)+(t.quantity*t.price))/net_qty[t.symbol];
            }
        else if(t.side=="SELL"){
            double old_qty=net_qty[t.symbol];
            net_qty[t.symbol]=old_qty-t.quantity;
            double old_avg=avg_cost[t.symbol];
            if(net_qty[t.symbol]==0) {
                avg_cost[t.symbol]=0.0;
            }
                realized[t.symbol]+=(t.price-old_avg)*t.quantity;}
        }
 void Portfolio::save() {
        std::ofstream file("trades.csv");
        if(!(file.is_open())){
            std::cerr << "Cant open the file !" <<std::endl;
            return;
        }
        file << "symbol|side|quantity|price|timestamp|source"<<std::endl;
        for(const auto& t : trade){
            file << t.to_csv() << std::endl;
        }
    }
void Portfolio::load() {
        std::ifstream file("trades.csv");
        if(!(file.is_open())) {
            std::cerr << "Cant open the file !" <<std::endl;
            return;
        }

        std::string line;
        std::getline(file, line);
        while (std::getline(file,line)) {
            Trade t;

            std::stringstream ss(line);
            std::string token;
            int column=0;
            while (getline(ss,token,'|')) {
                switch(column) {
                    case 0: t.symbol=token; break;
                    case 1: t.side=token; break;
                    case 2: t.quantity=std::stod(token); break;
                    case 3: t.price=std::stod(token); break;
                    case 4: t.timestamp=token; break;
                    case 5: t.source=token; break;
                    default: break;
                }
                column++;
            }
            Portfolio::add_trade(t);
        }


    }
