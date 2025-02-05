# tarefa-29-01
tarefa professor ricardo
# Semáforo com Raspberry Pi Pico W

Este projeto implementa um semáforo com três LEDs (vermelho, azul e verde) controlados por um botão (pushbutton). Quando o botão é pressionado, o semáforo inicia seu ciclo: vermelho, azul e verde, com um intervalo de 3 segundos entre cada mudança.

## Requisitos

- Raspberry Pi Pico W
- 3 LEDs (vermelho, amarelo e verde)
- 3 Resistores de 330 Ω
- 1 Botão (Pushbutton)

## Conexões

- LED Vermelho: GPIO 13
- LED Amarelo: GPIO 12
- LED Verde: GPIO 11
- Botão: GPIO 5

## Como usar

1. Conecte os componentes conforme descrito acima.
2. Compile e carregue o código no Raspberry Pi Pico W.
3. Pressione o botão para iniciar o ciclo do semáforo.

## Observações

- O botão só pode ser pressionado novamente após o ciclo do semáforo ser concluído.
- O código inclui uma rotina de debounce para evitar leituras múltiplas do botão.

## Autor

[luan souza meira]
