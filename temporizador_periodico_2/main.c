#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Defina os pinos dos LEDs e do botão
#define LED_PIN_RED 11
#define LED_PIN_YELLOW 12
#define LED_PIN_GREEN 13
#define BUTTON_PIN 5

// Variável para controlar o estado do botão
bool button_pressed = false;

// Função de callback para o alarme (temporizador)
int64_t semaphore_callback(alarm_id_t id, void *user_data) {
    static int state = 0; // Controla o estado do semáforo (0: vermelho, 1: amarelo, 2: verde)

    switch (state) {
        case 0: // Vermelho
            gpio_put(LED_PIN_RED, true);
            gpio_put(LED_PIN_YELLOW, false);
            gpio_put(LED_PIN_GREEN, false);
            state = 1; // Próximo estado: amarelo
            break;
        case 1: // Amarelo
            gpio_put(LED_PIN_RED, false);
            gpio_put(LED_PIN_YELLOW, true);
            gpio_put(LED_PIN_GREEN, false);
            state = 2; // Próximo estado: verde
            break;
        case 2: // Verde
            gpio_put(LED_PIN_RED, false);
            gpio_put(LED_PIN_YELLOW, false);
            gpio_put(LED_PIN_GREEN, true);
            state = 0; // Próximo estado: vermelho
            button_pressed = false; // Permite que o botão seja pressionado novamente
            return 0; // Finaliza o ciclo do semáforo
    }

    // Configura o próximo alarme para 3 segundos
    add_alarm_in_ms(3000, semaphore_callback, NULL, false);

    // Retorna 0 para indicar que o alarme atual não deve ser repetido
    return 0;
}

// Função de callback para o botão
void button_callback(uint gpio, uint32_t events) {
    static absolute_time_t last_press_time = 0; // Armazena o tempo do último pressionamento
    absolute_time_t current_time = get_absolute_time(); // Obtém o tempo atual

    // Verifica se o botão foi pressionado recentemente (debounce)
    if (absolute_time_diff_us(last_press_time, current_time) > 200000) { // 200ms de debounce
        if (!button_pressed) {
            // Inicia o semáforo
            button_pressed = true;

            // Configura o alarme para mudar o estado do semáforo após 3 segundos
            add_alarm_in_ms(3000, semaphore_callback, NULL, false);

            // Liga o LED vermelho inicialmente
            gpio_put(LED_PIN_RED, true);
            gpio_put(LED_PIN_YELLOW, false);
            gpio_put(LED_PIN_GREEN, false);
        }
        last_press_time = current_time; // Atualiza o tempo do último pressionamento
    }
}

int main() {
    // Inicializa a biblioteca padrão do Pico
    stdio_init_all();

    // Configura os pinos dos LEDs como saída
    gpio_init(LED_PIN_RED);
    gpio_init(LED_PIN_YELLOW);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_set_dir(LED_PIN_YELLOW, GPIO_OUT);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    // Configura o pino do botão como entrada
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN); // Habilita o resistor de pull-up interno

    // Configura a interrupção para o botão
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    // Loop principal
    while (true) {
        // Aqui você pode adicionar outras lógicas, se necessário
        tight_loop_contents();
    }

    return 0;
}