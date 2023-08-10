//+------------------------------------------------------------------+
//|                                                      structs.hpp |
//|                                                    OnTick Invest |
//|                                                www.ontick.com.br |
//+------------------------------------------------------------------+

#pragma once
#include <iostream>

//
struct STR_BAR
  {
    time_t date_time_t = 0;
    double open = 0;
    double high = 0;
    double low = 0;
    double close = 0;
    int trades = 0;
    double volume = 0
  };

//
struct EXEC_REPORT
  {
    int ret_code;
    std::string order_id;
    double volume_total;
    double volume_filled;
    double price_avg;
    ORDER_STATE order_state;
    int latency_ms;
  };