# Padrões de candlesticks

## Martelo (hammer)
``` C++
auto prev_bar = tf.PrevBar();
bool pattern = (prev_bar.close==prev_bar.high) && 
               (prev_bar.close>prev_bar.open) &&
               (prev_bar.open>prev_bar.low) &&
               ((prev_bar.open-prev_bar.low)>=2*(prev_bar.close-prev_bar.open));
```

## Martelo invertido (inverted hammer)
``` C++
auto prev_bar = tf.PrevBar();
bool pattern = (prev_bar.close==prev_bar.low) && 
               (prev_bar.close<prev_bar.open) &&
               (prev_bar.open<prev_bar.high) &&
               ((prev_bar.high-prev_bar.open)>=2*(prev_bar.open-prev_bar.close));
```

## Doji
``` C++
auto prev_bar = tf.PrevBar();
bool pattern = (prev_bar.open==prev_bar.close) && 
               (prev_bar.close<prev_bar.high) &&
               (prev_bar.close>prev_bar.low);
```