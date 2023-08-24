//+------------------------------------------------------------------+
//|                                              trade_interface.hpp |
//|                                                    OnTick Invest |
//|                                                www.ontick.com.br |
//+------------------------------------------------------------------+

#ifndef __TRADE_INTERFACE__
#define __TRADE_INTERFACE__

#pragma once
#include <iostream>

//+------------------------------------------------------------------+
//| CTradeInterface Class                                            |
//+------------------------------------------------------------------+
class CTradeInterface
  {
private:
    //
public:
    //
    std::pair<int,std::string>         BuyMarket(CSymbolsInterface _symbol, int _volume, float _tp, float _sl, const std::string &_comment);
    std::pair<int,std::string>         SellMarket(CSymbolsInterface _symbol, int _volume, float _tp, float _sl, const std::string &_comment);
    //
    void                               CloseAll(CSymbolsInterface _symbol);
  };

#endif