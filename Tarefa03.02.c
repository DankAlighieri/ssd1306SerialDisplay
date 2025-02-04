#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "lib/ssd1306.h"
#include "lib/button.h"
#include "lib/matriz_leds.h"
#include "lib/led.h"

#define I2C_SDA 14
#define I2C_SDL 15
/*
#define UART_TX 0
#define UART_RX 1
*/
#define BTN_A 5
#define BTN_B 6
#define LED_G 11
#define LED_B 12
#define MATRIX_PIN 7

extern Matriz_leds_config* numeros[];

// Variáveis voláteis para gerenciar o debounce de cada botão
static volatile uint32_t last_time = 0;

static volatile uint8_t number;

static volatile bool led_g_state = false;
static volatile bool led_b_state = false;

static volatile bool display_ligado_led = false;

PIO pio;
uint sm;

uint8_t ssd[ssd1306_buffer_length];

// Prepara o canva do display
struct render_area frame_area = {
    start_column : 0,
    end_column : ssd1306_width - 1,
    start_page : 0,
    end_page : ssd1306_n_pages - 1
};

static void gpio_irq_handler(uint gpio, uint32_t events);

static bool debounce_time(uint32_t *last_time);
/*

void on_uart_rx() {
    while(uart_is_readable(uart0)){
        char c = uart_getc(uart0);
        uart_char_received = true;
        uart_char = c;
        if (c >= '0' && c <= '9'){
            imprimir_desenho(*numeros[c - '0'], pio, sm);
        } else {
            ssd1306_draw_char(ssd, 10, 10, c);
            render_on_display(ssd, &frame_area);    
        }
    }
}
*/

int main() {
    char input;

    stdio_init_all();

    button_init(BTN_A);
    button_init(BTN_B);
    led_init(LED_G);
    led_init(LED_B);

    // Configuracoes da matriz
    pio = pio0;
    sm = configurar_matriz(pio, MATRIX_PIN);
    
    // inicializando uart
    uart_init(uart0, 115200);

   /*
    gpio_set_function(UART_TX, GPIO_FUNC_UART); // Configurando TX
    gpio_set_function(UART_RX, GPIO_FUNC_UART); // Configurando RX

    uart_set_fifo_enabled(uart0, true);

    // Configurando irq para uart
    irq_set_exclusive_handler(UART0_IRQ, on_uart_rx);
    irq_set_enabled(UART0_IRQ, true);

    uart_set_irq_enables(uart0, true, false);
   */
   
    // Inicializando display oled
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SDL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SDL);

    ssd1306_init();

    calculate_render_area_buffer_length(&frame_area);

    // zera o display inteiro
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);

    // desliga todos os leds da matriz
    imprimir_desenho(*numeros[10], pio, sm);

    // Ativando interrupcoes para os botoes
    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BTN_B, GPIO_IRQ_EDGE_FALL, true, gpio_irq_handler);

    while (true) {
        scanf("%c", &input);
        printf("%c", input);

        if(display_ligado_led) {
            memset(ssd, 0, ssd1306_buffer_length);
            render_on_display(ssd, &frame_area);
            display_ligado_led = false;
        }
                
        if (input >= '0' && input <= '9'){
            imprimir_desenho(*numeros[input - '0'], pio, sm);
        } else {
            imprimir_desenho(*numeros[10], pio, sm);
        }

        ssd1306_draw_char(ssd, 10, 10, input);
        render_on_display(ssd, &frame_area);    
        sleep_ms(300);
    }
}

static void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    char *text[4] ={ "", "" };

    if(debounce_time(&last_time)) {
        if(gpio == BTN_A) {     
            led_g_state = !led_g_state;
            gpio_put(LED_G, led_g_state);

            if (led_g_state) {
                text[0] = "  LED Verde  ";
                text[1] = "   ligado  ";
                printf("LED verde ligado\n");
            } else {
                text[0] = "  LED Verde  ";
                text[1] = "  desligado  ";
                printf("LED verde desligado\n");
            }
        } else if (gpio == BTN_B) {
            led_b_state = !led_b_state;
            gpio_put(LED_B, led_b_state);

            if (led_b_state) {
                text[0] = "  LED Azul  ";
                text[1] = "   ligado  ";
                printf("LED azul ligado\n");
            } else {
                text[0] = "  LED Azul  ";
                text[1] = "  desligado  ";
                printf("LED azul desligado\n");
            }
        }
        display_ligado_led = true;
    }
    int y = 0;
    for(uint8_t i = 0; i < count_of(text); i++) {
        ssd1306_draw_string(ssd, 5, y, text[i]);
        y += 8;
    }
    render_on_display(ssd, &frame_area);
}

static bool debounce_time(uint32_t *last_time) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    if(current_time - *last_time > 200000) {
        *last_time = current_time;
        return true;
    }
    return false;
}