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
int volume = 1; // volume das operações
int short_ma_period = 8;
int long_ma_period = 20;
std::string short_ma_type = "MODE_SMA";
std::string long_ma_type = "MODE_EMA";

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
    volume = (inputs.Exists("volume")) ? std::stoi(inputs.GetStrategyParam("volume")) : 1;
    short_ma_period = (inputs.Exists("short_ma_period")) ? std::stoi(inputs.GetStrategyParam("short_ma_period")) : 8;
    short_ma_type = (inputs.Exists("short_ma_type")) ? inputs.GetStrategyParam("short_ma_type") : "MODE_SMA";
    long_ma_period = (inputs.Exists("long_ma_period")) ? std::stoi(inputs.GetStrategyParam("long_ma_period")) : 20;
    long_ma_type = (inputs.Exists("long_ma_type")) ? inputs.GetStrategyParam("long_ma_type") : "MODE_EMA";

    // média curta
    params.Reset();
    params.AddVariable("ma_period",short_ma_period);
    params.AddVariable("ma_method",short_ma_type);
    ma_short.Init(tf1,IND_MA,params);

    // média longa
    params.Reset();
    params.AddVariable("ma_period",long_ma_period);
    params.AddVariable("ma_method",long_ma_type);
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
                trade.BuyMarket(symbol,volume,0,0,"[IN] Compra a mercado");
              }
            // se tiver posição
            else
              {
                // caso vendido (vira a mão)
                if(position.PositionType(symbol)==POSITION_TYPE_SELL) trade.BuyMarket(symbol,position.PositionVolume(symbol)+volume,0,0,"[REV] Compra a mercado");
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
                trade.SellMarket(symbol,volume,0,0,"[IN] Venda a mercado");
              }
            // se tiver posição, vira a mão
            else
              {
                // caso comprado (vira a mão)
                if(position.PositionType(symbol)==POSITION_TYPE_BUY) trade.SellMarket(symbol,position.PositionVolume(symbol)+volume,0,0,"[REV] Venda a mercado");
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
        if(position.PositionType(symbol)==POSITION_TYPE_BUY)
          {
            trade.SellMarket(symbol,position.PositionVolume(symbol),0,0,"[EXIT] Venda a mercado");
          }
        else
          {
            trade.BuyMarket(symbol,position.PositionVolume(symbol),0,0,"[EXIT] Compra a mercado");
          }
      }
  }