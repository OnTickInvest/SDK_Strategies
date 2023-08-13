//+------------------------------------------------------------------+
//|                                                          app.cpp |
//|                                                    OnTick Invest |
//|                                                www.ontick.com.br |
//+------------------------------------------------------------------+

#include "../src/ontick.hpp"

//
COnTick ontick;
CInputsInterface inputs;
CSymbolsInterface symbol;
CTimeframe tf1;
CParams params;
CIndicatorsInterface ma_short;
CIndicatorsInterface ma_long;
CTradeInterface trade;
CPositionsInterface position;

//+------------------------------------------------------------------+
//| INPUTS                                                           |
//+------------------------------------------------------------------+
int inp_volume = 1; // volume das operações
int inp_short_ma_period = 8;
int inp_long_ma_period = 20;
std::string inp_short_ma_type = "MODE_SMA";
std::string inp_long_ma_type = "MODE_EMA";

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
    inp_short_ma_period = (inputs.Exists("short_ma_period")) ? std::stoi(inputs.GetStrategyParam("short_ma_period")) : 8;
    inp_short_ma_type = (inputs.Exists("short_ma_type")) ? inputs.GetStrategyParam("short_ma_type") : "MODE_SMA";
    inp_long_ma_period = (inputs.Exists("long_ma_period")) ? std::stoi(inputs.GetStrategyParam("long_ma_period")) : 20;
    inp_long_ma_type = (inputs.Exists("long_ma_type")) ? inputs.GetStrategyParam("long_ma_type") : "MODE_EMA";

    // média curta
    params.Reset();
    params.AddVariable("ma_period",inp_short_ma_period);
    params.AddVariable("ma_method",inp_short_ma_type);
    ma_short.Init(tf1,IND_MA,params);

    // média longa
    params.Reset();
    params.AddVariable("ma_period",inp_long_ma_period);
    params.AddVariable("ma_method",inp_long_ma_type);
    ma_long.Init(tf1,IND_MA,params);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CApplication::OnTick(void)
  {
    // a cada nova barra
    if(tf1.IsNewBar())
      {
        // cruzamento para cima
        if( ma_short.ValueAt(0,1)>ma_long.ValueAt(0,1) && ma_short.ValueAt(0,2)<ma_long.ValueAt(0,2) )
          {
            std::cout << "[INFO] CRUZAMENTO PRA CIMA" << std::endl;
            // caso sem posição
            if(!position.PositionFound(symbol))
              {
                trade.BuyMarket(symbol,inp_volume,0,0,"[IN] Compra a mercado");
              }
            // se tiver posição
            else
              {
                // caso vendido (vira a mão)
                if(position.PositionType(symbol)==POSITION_TYPE_SELL) trade.BuyMarket(symbol,position.PositionVolume(symbol)+inp_volume,0,0,"[REV] Compra a mercado");
                // caso comprado (não faz nada)
              }
          }
        
        // cruzamento para baixo
        if( ma_short.ValueAt(0,1)<ma_long.ValueAt(0,1) && ma_short.ValueAt(0,2)>ma_long.ValueAt(0,2) )
          {
            std::cout << "[INFO] CRUZAMENTO PRA BAIXO" << std::endl;
            // caso sem posição
            if(!position.PositionFound(symbol))
              {
                trade.SellMarket(symbol,inp_volume,0,0,"[IN] Venda a mercado");
              }
            // se tiver posição, vira a mão
            else
              {
                // caso comprado (vira a mão)
                if(position.PositionType(symbol)==POSITION_TYPE_BUY) trade.SellMarket(symbol,position.PositionVolume(symbol)+inp_volume,0,0,"[REV] Venda a mercado");
                // caso vendido (não faz nada)
              }
          }
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