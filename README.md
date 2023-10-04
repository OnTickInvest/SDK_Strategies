# SDK_Strategies
Repositório público de estratégias desenvolvidas com a SDK da OnTick Invest

# Histórico de versões

### 0.7-alpha (em desenvolvimento):
- Suporte a gráficos atemporais (renko / range / pontos / trades / volume)
- Suporte a gráficos de segundos
- Alteração de variáveis de indicadores de double para float
### 0.6-alpha (17/09/2023):
- Implementação da função de manipulação de eventos OnTimer
- Implementação da função de manipulação de eventos OnTrade
- Implementação da classe [CLoggerInterface](docs/includes/logger_interface.hpp)
- Implementação da classe [CTimeInterface](docs/includes/time_interface.hpp)
- Implementação de múltiplos IP's no whitelisting

### 0.5-alpha (15/08/2023):
- Implementação da classe [CInputsInterface](docs/includes/inputs_interface.hpp)
- Apresentação de informações sobre IP whitelisting
- Implementação da lógica anti-looping (rate limit de ordens)
- Implementação de TP/SL automáticos
- Atualização de [exemplos](examples) e [configs](configs/configs.json)

### 0.4-alpha (08/08/2023):
- Carregamento de posições abertas ao incializar
- Inclusão de novas funções na interface de posições
- Implementação de envio de ordens e requisições na função OnDeinit

### 0.3-alpha (07/08/2023):
- Envio de ordens a mercado
- Implementação da lógica de login/logout/heartbeats

### 0.2-alpha (25/07/2023):
- Cálculo de indicadores técnicos (ATR, MA, HILO, ADX, BB, RSI)

### 0.1-alpha (20/07/2023):
- Transmissão de market data binário (top-of-book)
- Transmissão de histórico OHLC
