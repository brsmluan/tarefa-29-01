#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Defina os pinos dos LEDs RGB
#define LED_PIN_RED 11
#define LED_PIN_GREEN 12
#define LED_PIN_BLUE 13

// Variável para controlar o estado do LED
bool led_on = false;

// Função de callback do temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    static int state = 0; // Controla o estado do semáforo (0: vermelho, 1: amarelo, 2: verde)

    // Imprime uma mensagem na saída serial a cada segundo
    printf("1 segundo passou\n");

    // Lógica para mudar o estado do semáforo
    switch (state) {
        case 0: // Vermelho
            gpio_put(LED_PIN_RED, true);
            gpio_put(LED_PIN_GREEN, false);
            gpio_put(LED_PIN_BLUE, false);
            break;
        case 1: // azul 
            gpio_put(LED_PIN_RED, false);
            gpio_put(LED_PIN_GREEN, false);
            gpio_put(LED_PIN_BLUE, true);
            break;
        case 2: // Verde
            gpio_put(LED_PIN_RED, false);
            gpio_put(LED_PIN_GREEN, true);
            gpio_put(LED_PIN_BLUE, false);
            break;
    }

    // Avança para o próximo estado
    state = (state + 1) % 3;

    // Retorna true para manter o temporizador repetindo
    return true;
}

int main() {
    // Inicializa a biblioteca padrão do Pico
    stdio_init_all();

    // Configura os pinos dos LEDs como saída
    gpio_init(LED_PIN_RED);
    gpio_init(LED_PIN_GREEN);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);

    // Inicializa o temporizador repetitivo com um intervalo de 3 segundos (3000 ms)
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal
    while (true) {
        // Aqui você pode adicionar outras lógicas, se necessário
        tight_loop_contents();
    }

    return 0;
}