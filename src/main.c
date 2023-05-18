#include "stm32f103xb.h" // Inicjalizacja zmiennej wskaźnika opóźnienia
#include "timery.h"
#include "uart.h"
#include "ftoa.h"
#include <string.h>
#include "../include/configure_GPIO_inputs.h"

volatile uint8_t isButtonPressed;
#define BUFFER_SIZE 64
char buffer[BUFFER_SIZE];
int buffer_index = 0;

// Funkcja główna
int main(void)
{
    SysTick_Config(4095);                         // Domyślnie: SysTick_Config(8000);
    SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk; // 8000000/8

    // Inicjalizacja przycisku
    // button_init();

    // Inicjalizacja timera
    timer1_init();

    // Włącz NVIC dla przerwań timera1
    NVIC_EnableIRQ(TIM1_UP_IRQn);
    NVIC_EnableIRQ(TIM2_IRQn);
    uart_init();

    // Konfiguracja portów
    configure_GPIO_inputs();

    couter_enable();
    char wynik_cstring[10];

    // Pętla główna
    while (1)
    {
        if (odczytano == 1)
        {
            if (odleglosc_cm <= 40)
            {
                GPIOA->ODR |= GPIO_ODR_ODR1;
            }
            else
            {
                GPIOA->ODR &= ~GPIO_ODR_ODR1;
            }

            ftoa(odleglosc_cm, wynik_cstring, 2);
            USART1_SendCString(wynik_cstring, 10);
            USART1_SendByte('\n');
            odczytano = 0;
        }
    }
}
