//+------------------------------------------------------------------+
//|                                               time_interface.hpp |
//|                                                    OnTick Invest |
//|                                                www.ontick.com.br |
//+------------------------------------------------------------------+

#ifndef __TIME_INTERFACE__
#define __TIME_INTERFACE__

#pragma once
#include <iostream>

//+------------------------------------------------------------------+
//| CTimeInterface Class                                             |
//+------------------------------------------------------------------+
class CTimeInterface
  {
public:
    //
    void                               GetFromStrategy(void);
    void                               SetTimeLimits(int _start_hour, int _start_minute, int _limit_hour, int _limit_minute, int _finish_hour, int _finish_minute);
    void                               SetAllowedDays(bool _sun, bool _mon, bool _tue, bool _wed, bool _thu, bool _fri, bool _sat);
    //
    bool                               TimeAllowed(void);
    bool                               OpenAllowed(void);
    bool                               DayAllowed(void);
  };

#endif