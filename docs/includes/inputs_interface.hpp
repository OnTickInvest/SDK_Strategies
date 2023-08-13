//+------------------------------------------------------------------+
//|                                             inputs_interface.hpp |
//|                                                    OnTick Invest |
//|                                                www.ontick.com.br |
//+------------------------------------------------------------------+

#ifndef __INPUTS_INTERFACE__
#define __INPUTS_INTERFACE__

#pragma once
#include <iostream>

//+------------------------------------------------------------------+
//| CInputsInterface Class                                           |
//+------------------------------------------------------------------+
class CInputsInterface
  {
public:
    bool                               Exists(const std::string &_variable_name);
    std::string                        GetStrategyParam(const std::string &_variable_name);
  };

#endif