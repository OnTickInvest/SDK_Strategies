//+------------------------------------------------------------------+
//|                                                        enums.hpp |
//|                                                    OnTick Invest |
//|                                                www.ontick.com.br |
//+------------------------------------------------------------------+

#pragma once
#include <iostream>

//
enum ENUM_POSITION_TYPE
  {
    POSITION_TYPE_NONE,
    POSITION_TYPE_BUY,
    POSITION_TYPE_SELL
  };

//
enum ORDER_STATE
  {
    ORDER_STARTED,
    ORDER_PLACED,
    ORDER_CANCELED,
    ORDER_PARTIAL,
    ORDER_FILLED,
    ORDER_REJECTED,
    ORDER_EXPIRED,
    ORDER_ERROR
  };

//
enum ENUM_INDICATORS
  {
    IND_ADX,
    IND_ATR,
    IND_BB,
    IND_CCI,
    IND_HILO,
    IND_HMA,
    IND_KELTNER,
    IND_MA,
    IND_MACD,
    IND_PP,
    IND_PSAR,
    IND_RSI,
    IND_STOCH,
    IND_VWAP
  };