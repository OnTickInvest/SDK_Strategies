//+------------------------------------------------------------------+
//|                                             logger_interface.hpp |
//|                                                    OnTick Invest |
//|                                                www.ontick.com.br |
//+------------------------------------------------------------------+

#ifndef __LOGGER_INTERFACE__
#define __LOGGER_INTERFACE__

#pragma once
#include <iostream>

//+------------------------------------------------------------------+
//| CLoggerInterface Class                                           |
//+------------------------------------------------------------------+
class CLoggerInterface
  {
public:
    bool                               SaveLog(const std::string &_log_type, const std::string &_log_msg);
  };

#endif