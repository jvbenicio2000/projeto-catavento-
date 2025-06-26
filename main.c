#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

#define POT_PIN 26
#define STEP_PIN 22
#define DIR_PIN 21
#define ENABLE_PIN 20
#define TENS_PIN 27
#define LED_PIN 19

int posicao = 0;
float motor = 0;
int passo = 0;
int valor = 0;
float angulo = 0;
float valor_bruto = 0;
char* direcao;

void setup() {
    stdio_init_all();

    gpio_init(STEP_PIN); gpio_set_dir(STEP_PIN, GPIO_OUT);
    gpio_init(DIR_PIN);  gpio_set_dir(DIR_PIN, GPIO_OUT);
    gpio_init(ENABLE_PIN); gpio_set_dir(ENABLE_PIN, GPIO_OUT);
    gpio_put(ENABLE_PIN, 0); // Habilita driver

    gpio_init(LED_PIN); gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN);
    pwm_set_wrap(slice_num, 65535);
    pwm_set_enabled(slice_num, true);

    adc_init();
    adc_gpio_init(POT_PIN);
    adc_gpio_init(TENS_PIN);
}

int ler_potenciometro() {
    adc_select_input(0); // ADC0 -> GP26
    uint16_t raw = adc_read();
    valor = raw >> 4;
    return valor;
}

float converte_angulo() {
    angulo = roundf((valor * 360.0f / 4095.0f) * 100) / 100;
    return angulo;
}

int converte_passo() {
    passo = (int)(angulo / 0.1125f);
    return passo;
}

void controla_motor() {
    motor = roundf(posicao * 0.1125f * 100) / 100;
    if ((posicao - passo) > 0) {
        gpio_put(DIR_PIN, 0);
        direcao = "anti-horário";
        gpio_put(STEP_PIN, 1);
        sleep_us(50);
        gpio_put(STEP_PIN, 0);
        posicao--;
    } else if ((posicao - passo) < 0) {
        gpio_put(DIR_PIN, 1);
        direcao = "horário";
        gpio_put(STEP_PIN, 1);
        sleep_us(50);
        gpio_put(STEP_PIN, 0);
        posicao++;
    }
    if (passo == posicao) {
        sleep_ms(1000);
    }
}

float le_tensao_motor() {
    adc_select_input(1); // ADC1 -> GP27
    uint16_t raw = adc_read();
    valor_bruto = (raw >> 4) / 4095.0f * 3.3f;
    sleep_us(100);
    return valor_bruto;
}

void controla_led(float valor) {
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN);
    if (valor > 0.01f) {
        pwm_set_gpio_level(LED_PIN, 65535);
    } else {
        pwm_set_gpio_level(LED_PIN, 0);
    }
}

int main() {
    setup();
    while (1) {
        ler_potenciometro();
        converte_angulo();
        converte_passo();
        controla_motor();
        le_tensao_motor();
        controla_led(valor_bruto);
        printf("Potenciometro: %d, Angulo Pot: %.2f, Angulo Motor: %.2f, Passo: %d, Posicao Motor: %d, Direcao: %s\n",
               valor, angulo, motor, passo, posicao, direcao);
    }
    return 0;
}
