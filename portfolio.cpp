#include "portfolio.h"
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
