//+------------------------------------------------------------------+
//|                                         timeframes_interface.hpp |
//|                                                    OnTick Invest |
//|                                                www.ontick.com.br |
//+------------------------------------------------------------------+

#ifndef __TIMEFRAMES_INTERFACE__
#define __TIMEFRAMES_INTERFACE__

#pragma once
#include <iostream>

//+------------------------------------------------------------------+
//| CTimeframe Class                                                 |
//+------------------------------------------------------------------+
class CTimeframe
  { 
private:
    std::string                        m_timeframe_id;
public:
    //
    void                               Init(CSymbolsInterface _symbol,const std::string &_timeframe);
    void                               GetFromRuntime(CSymbolsInterface _symbol);
    std::string                        TimeframeId(void);
    //
    bool                               IsNewBar(void);
    STR_BAR                            CurrBar(void);
    STR_BAR                            PrevBar(void);
    STR_BAR                            BarAt(int _pos);
  };

#endif