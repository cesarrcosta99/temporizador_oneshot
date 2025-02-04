#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos pinos (BitDogLab)
#define LED_VERMELHO 13   // GPIO13
#define LED_AZUL 12       // GPIO12
#define LED_VERDE 11      // GPIO11
#define BUTTON_PIN 5      // GPIO5

// Estados do sistema
enum Estados {
    TODOS_LIGADOS,
    DESLIGAR_AZUL,
    DESLIGAR_VERMELHO,
    DESLIGAR_VERDE
};

// Variáveis globais
static bool sequencia_ativa = false;
static absolute_time_t ultimo_clique;

// Função de callback para controle dos LEDs
int64_t callback_temporizador(alarm_id_t id, void *user_data) {
    int estado = (int)user_data;

    switch(estado) {
        case DESLIGAR_AZUL:
            gpio_put(LED_AZUL, 0);
            add_alarm_in_ms(3000, callback_temporizador, (void*)DESLIGAR_VERMELHO, false);
            break;
            
        case DESLIGAR_VERMELHO:
            gpio_put(LED_VERMELHO, 0);
            add_alarm_in_ms(3000, callback_temporizador, (void*)DESLIGAR_VERDE, false);
            break;
            
        case DESLIGAR_VERDE:
            gpio_put(LED_VERDE, 0);
            sequencia_ativa = false; // Libera o botão
            break;
    }
    
    return 0;
}

// Função principal
int main() {
    stdio_init_all();
    
    // Configuração dos LEDs
    gpio_init(LED_VERMELHO);
    gpio_init(LED_AZUL);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Configuração do botão
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    
    // Variável para debounce
    ultimo_clique = get_absolute_time();

    while(1) {
        // Verifica clique válido (com debounce)
        if(gpio_get(BUTTON_PIN) == 0 && !sequencia_ativa) {
            absolute_time_t agora = get_absolute_time();
            
            // Debounce de 50ms
            if(absolute_time_diff_us(ultimo_clique, agora) > 50000) {
                ultimo_clique = agora;
                
                // Liga todos os LEDs
                gpio_put(LED_VERMELHO, 1);
                gpio_put(LED_AZUL, 1);
                gpio_put(LED_VERDE, 1);
                
                // Inicia sequência
                sequencia_ativa = true;
                add_alarm_in_ms(3000, callback_temporizador, (void*)DESLIGAR_AZUL, false);
            }
        }
        sleep_ms(10);
    }
    
    return 0;
}