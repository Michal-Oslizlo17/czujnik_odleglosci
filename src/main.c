#include "stm32f103xb.h"
#include "timery.h"
#include "uart.h"
#include "ftoa.h"
#include <string.h>
#include "../include/configure_GPIO_inputs.h"
#include "../include/wyswietlacze.h"

volatile uint8_t isButtonPressed;
#define BUFFER_SIZE 64
char buffer[BUFFER_SIZE];
int buffer_index = 0;

// Funkcja główna
int main(void)
{
    SysTick_Config(4095);
    SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;

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
        // if (odczytano == 1)
        // {
        //     if (odleglosc_cm <= 40)
        //     {
        //         GPIOA->ODR |= GPIO_ODR_ODR1;
        //     }
        //     else
        //     {
        //         GPIOA->ODR &= ~GPIO_ODR_ODR1;
        //     }

        //     ftoa(odleglosc_cm, wynik_cstring, 2);
        //     USART1_SendCString(wynik_cstring, 10);
        //     USART1_SendByte('\n');
        //     odczytano = 0;
        // }
        
        // Jeśli odczytano dane, przetwórz je i wyświetl na wyświetlaczach
        if (odczytano == 1)
        {
            ftoa(odleglosc_cm, wynik_cstring, 2);
            USART1_SendCString(wynik_cstring, 10);
            USART1_SendByte('\n');

            char *comma_pos = strchr(wynik_cstring, ',');
            
            if (comma_pos != NULL)
            {
                *comma_pos = '\0';

                int distance_int = atoi(wynik_cstring);
                int fraction_int = atoi(comma_pos + 1);

                wlacz_wyswietlacz(0, 1, 0);
                wlacz_wyswietlacz(0, 2, 0);
                wlacz_wyswietlacz(0, 3, 0);
                wlacz_wyswietlacz(0, 4, 0);

                int digit = 0;
                int number = distance_int;
                int numer_wyswietlacza = 1;

                while (number > 0 && numer_wyswietlacza <= 4)
                {
                    digit = number % 10;
                    number /= 10;
                    wlacz_wyswietlacz(digit, numer_wyswietlacza, 1);
                    numer_wyswietlacza++;
                }

                number = fraction_int;
                numer_wyswietlacza = 1;

                while (number > 0 && numer_wyswietlacza <= 2)
                {
                    digit = number % 10;
                    number /= 10;
                    // wlacz_wyswietlacz(digit, numer_wyswietlacza + 2);
                    // numer_wyswietlacza++;
                }
            }

            odczytano = 0;
        }

        // wyswietlacz_liczba_jeden(0);
        // wyswietlacz_liczba_dwa(0);
        // wyswietlacz_liczba_trzy(0);
        // wyswietlacz_liczba_cztery(0);

        // wyswietlacz_liczba_jeden(1);
        // wyswietlacz_segment_a(1);
        // wyswietlacz_segment_b(1);
        // wyswietlacz_segment_c(1);
        // wyswietlacz_segment_d(1);
        // wyswietlacz_segment_e(1);
        // wyswietlacz_segment_f(1);
        // wyswietlacz_segment_g(1);
        // wyswietlacz_liczba_jeden(0);

        // wyswietlacz_liczba_dwa(1);
        // wyswietlacz_segment_a(1);
        // wyswietlacz_segment_b(1);
        // wyswietlacz_segment_c(1);
        // wyswietlacz_segment_d(1);
        // wyswietlacz_segment_e(1);
        // wyswietlacz_segment_f(1);
        // wyswietlacz_segment_g(1);
        // wyswietlacz_liczba_dwa(0);

        // wyswietlacz_liczba_trzy(1);
        // wyswietlacz_segment_a(1);
        // wyswietlacz_segment_b(1);
        // wyswietlacz_segment_c(1);
        // wyswietlacz_segment_d(1);
        // wyswietlacz_segment_e(1);
        // wyswietlacz_segment_f(1);
        // wyswietlacz_segment_g(1);
        // wyswietlacz_liczba_trzy(0);

        // wyswietlacz_liczba_cztery(1);
        // wyswietlacz_segment_a(1);
        // wyswietlacz_segment_b(1);
        // wyswietlacz_segment_c(1);
        // wyswietlacz_segment_d(1);
        // wyswietlacz_segment_e(1);
        // wyswietlacz_segment_f(1);
        // wyswietlacz_segment_g(1);
        // wyswietlacz_liczba_cztery(0);
    }
}

// TODO

//zrobić funkcje

//wlacz_wyswietlacz(jaka cyfra, jaki numer_wyswietlacza, wlacz/wylacz)
