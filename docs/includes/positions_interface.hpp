//+------------------------------------------------------------------+
//|                                          positions_interface.hpp |
//|                                                    OnTick Invest |
//|                                                www.ontick.com.br |
//+------------------------------------------------------------------+

#ifndef __POSITIONS_INTERFACE__
#define __POSITIONS_INTERFACE__

#pragma once
#include <iostream>

//+------------------------------------------------------------------+
//| CPositionsInterface Class                                        |
//+------------------------------------------------------------------+
class CPositionsInterface
  {
private:
    //
public:
    //
    bool                               PositionFound(CSymbolsInterface _symbol);
    ENUM_POSITION_TYPE                 PositionType(CSymbolsInterface _symbol);
    //
    int                                PositionVolume(CSymbolsInterface _symbol);
    double                             PositionPrice(CSymbolsInterface _symbol);
    double                             PositionSL(CSymbolsInterface _symbol);
    double                             PositionTP(CSymbolsInterface _symbol);
    double                             PositionProfit(CSymbolsInterface _symbol);
    std::string                        PositionTimeOpen(CSymbolsInterface _symbol);
    std::string                        PositionTimeCurrent(CSymbolsInterface _symbol);
    std::string                        PositionComment(CSymbolsInterface _symbol);
  };

#endif