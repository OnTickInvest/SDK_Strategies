//+------------------------------------------------------------------+
//|                                                          app.cpp |
//|                                                    OnTick Invest |
//|                                                www.ontick.com.br |
//+------------------------------------------------------------------+

#include "../src/ontick.hpp"

//
COnTick ontick;
CSymbolsInterface symbol;
CTimeframe tf1;
CParams params;
CIndicatorsInterface rsi;
CTradeInterface trade;
CPositionsInterface position;

//+------------------------------------------------------------------+
//| INPUTS                                                           |
//+------------------------------------------------------------------+
int inp_volume = 1; // volume das operações
int inp_rsi_period = 2;

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
int main(int argc,char *argv[])
  {
    if(!ontick.Start(argc,argv)) return -1;
    ontick.Run();
    ontick.Stop();
    return 0;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CApplication::OnInit(void)
  {
    std::cout << "CApplication::OnInit() called" << std::endl;

    // carrega o ativo e o timeframe do arquivo de configs
    symbol.GetFromRuntime();
    tf1.GetFromRuntime(symbol);

    // associação de inputs deve acontecer dentro de OnInit
    inp_volume = (inputs.Exists("volume")) ? std::stoi(inputs.GetStrategyParam("volume")) : 1;
    inp_rsi_period = (inputs.Exists("rsi_period")) ? std::stoi(inputs.GetStrategyParam("rsi_period")) : 2;

    // IFR
    params.Reset();
    params.AddVariable("rsi_period",rsi_period);
    rsi.Init(tf1,IND_RSI,params);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CApplication::OnTick(void)
  {
    // a cada nova barra
    if(tf1.IsNewBar())
      {
        //  
      }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CApplication::OnTrade(EXEC_REPORT _exec_report)
  {
    std::cout << "CApplication::OnTrade()" << std::endl;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CApplication::OnDeinit(void)
  {
    std::cout << "CApplication::OnDeinit() called" << std::endl;
    if(position.PositionFound(symbol))
      {
        int curr_pos_volume = position.PositionVolume(symbol);
        //
        if(position.PositionType(symbol)==POSITION_TYPE_BUY)
          {
            trade.SellMarket(symbol,curr_pos_volume,0,0,"[EXIT] Venda a mercado");
          }
        else
          {
            trade.BuyMarket(symbol,curr_pos_volume,0,0,"[EXIT] Compra a mercado");
          }
      }
  }