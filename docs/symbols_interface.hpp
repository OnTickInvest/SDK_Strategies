//+------------------------------------------------------------------+
//|                                            symbols_interface.hpp |
//|                                                    OnTick Invest |
//|                                                www.ontick.com.br |
//+------------------------------------------------------------------+

#ifndef __SYMBOLS_INTERFACE__
#define __SYMBOLS_INTERFACE__

#pragma once
#include <iostream>

//+------------------------------------------------------------------+
//| CSymbolsInterface Class                                          |
//+------------------------------------------------------------------+
class CSymbolsInterface
  {
private:
    std::string                        m_symbol_name;
public:
    //
    void                               Init(const std::string &_symbol_name);
    void                               GetFromRuntime(void);
    //
    std::string                        Name(void);
    double                             TickSize(void);
    double                             TickValue(void);
    double                             MinVolume(void);
    double                             MaxVolume(void);
    int                                DecimalPlaces(void);
    //
    time_t                             Time(void);
    int                                State(void);
    double                             Bid(void);
    int                                BidVolume(void);
    double                             Ask(void);
    int                                AskVolume(void);
    double                             Last(void);
    int                                DailyTrades(void);
    int                                DailyVolume(void);
  };

/*
[State] Valid values:
  02 = Trading halt (Pause)
  04 = No-Open (Close)
  17 = Ready to trade (Open)
  18 = Not available for trading (Forbidden)
  20 = Unknown or invalid
  21 = Pre-Open (Reserved)
  101 = Final Closing Call
*/

#endif