//+------------------------------------------------------------------+
//|                                         indicators_interface.hpp |
//|                                                    OnTick Invest |
//|                                                www.ontick.com.br |
//+------------------------------------------------------------------+

#ifndef __INDICATORS_INTERFACE__
#define __INDICATORS_INTERFACE__

#pragma once
#include <iostream>

//
#include "../Params/params.hpp"

//+------------------------------------------------------------------+
//| CIndicatorsInterface Class                                       |
//+------------------------------------------------------------------+
class CIndicatorsInterface
  { 
private:
    //
    std::string                        m_indicator_id;
public:
    //
    void                               Init(CTimeframe _timeframe,ENUM_INDICATORS _indicator,CParams params);
    double                             ValueAt(int _buffer_number, int _position); // OBS: _position deve ser um valor de 0 a 199
    void                               PrintLastValues(int _num_values=5); // OBS: _num_values deve ser um valor de 1 a 10
  };

#endif