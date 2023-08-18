# Estrutura geral dos códigos de exemplo

## Inclusões e declarações
``` c++
//
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
```
- Para conseguir acessar todas as funcionalidades da SDK OnTick é necessário carregar o arquivo de header `ontick.hpp`
- Além do header, é necessário declarar instâncias de várias classes como `COnTick`, `CInputsInterface`, `CSymbolsInterface` e outras, que fazem parte do framework de negociação da SDK OnTick.

## Parâmetros de entrada (inputs)
``` c++
int inp_volume = 1; // volume das operações
int inp_short_ma_period = 8;
int inp_long_ma_period = 20;
std::string inp_short_ma_type = "MODE_SMA";
std::string inp_long_ma_type = "MODE_EMA";
```
- O código acima define variáveis de input (que devem ser nomeadas com o prefixo `inp_`), como `inp_volume`, `inp_short_ma_period`, `inp_long_ma_period`, `inp_short_ma_type` e `inp_long_ma_type`.
- Esses parâmetros controlam o comportamento da estratégia de negociação e podem ser definidos pelo usuário através da seção `strategy` do arquivo `configs.json`. Abaixo temos um exemplo de arquivo `configs.json`, onde é possível ver onde as variáveis devem ser definidas:
``` json
{
    "runtime": {
        
    },
    "strategy": {
        "volume": 1,
        "short_ma_period": 8,
        "short_ma_type": "MODE_SMA",
        "long_ma_period": 20,
        "long_ma_type": "MODE_EMA"
    }
}
```

## Função main
``` c++
int main(int argc,char *argv[])
  {
    if(!ontick.Start(argc,argv)) return -1;
    ontick.Run();
    ontick.Stop();
    return 0;
  }
```
- A função `main` é principal função de programas na linguagem C++. 
- Ela inicializa a classe `COnTick` (chamando `ontick.Start(argc,argv)`), executa a estratégia de negociação (chamando `ontick.Run()`) e quando necessário finaliza a estratégia (chamando `ontick.Stop()`).
- **IMPORTANTE: NENHUMA ALTERAÇÃO DEVE SER FEITA NESTA PARTE DO CÓDIGO!**

## Função OnInit
``` c++
void CApplication::OnInit(void)
```
- A função `OnInit` é chamada durante a fase de inicialização. Ela lê os valores dos parâmetros de entrada e inicializa indicadores com base nos inputs fornecidos no arquivo `configs.json`.

## Função OnTick
``` c++
void CApplication::OnTick(void)
```
- A função `OnTick` é o cerne da estratégia de negociação. Ela é executada a cada tick (mudança de preço) no mercado. Dentro dessa função, a estratégia verifica as condições da estratégia, enviando ordens de compra e venda com base nos critérios programados.

## Função OnTrade
``` c++
void CApplication::OnTrade(EXEC_REPORT _exec_report)
```
- A função `OnTrade` é chamada sempre que uma execução de negociação ocorre. Sempre que chamada, a função `OnTrade` atualiza a struct `_exec_report`, com todas as informações acerca da negociação que acabou de ocorrer. As variáveis contidas na struct `EXEC_REPORT` podem ser consultadas diretamente no arquivo [structs.hpp](../docs/structs/structs.hpp).

## Função OnDeinit
``` c++
void CApplication::OnDeinit(void)
  {
    if(position.PositionFound(symbol))
      {
        int curr_pos_volume = position.PositionVolume(symbol);
        if(position.PositionType(symbol)==POSITION_TYPE_BUY) trade.SellMarket(symbol,curr_pos_volume,0,0,"[EXIT] Venda a mercado");
        else trade.BuyMarket(symbol,curr_pos_volume,0,0,"[EXIT] Compra a mercado");
      }
  }
```
- A função `OnDeinit` é chamada quando o programa está prestes a ser fechado. No exemplo acima, ela verifica se há uma posição aberta e a fecha, colocando uma negociação oposta (vendendo se comprada, comprando se vendida) para encerrar eventuais posições abertas.

## Função OnTimer
``` c++
void CApplication::OnTimer(void)
```