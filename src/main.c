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

    char *comma_pos = strchr(wynik_cstring, ','); // Znajdź pozycję przecinka

    if (comma_pos != NULL)
    {
        *comma_pos = '\0'; // Zamień przecinek na znak zakończenia łańcucha [NIE MAM INNEGO POMYSŁU - CZASEM MA TO PROBLEM Z DZIAŁANIEM]

        int distance_int = atoi(wynik_cstring); // Przetwórz część przed przecinkiem na liczbę całkowitą
        int fraction_int = atoi(comma_pos + 1);  // Przetwórz część po przecinku na liczbę całkowitą

        // Wyłącz wszystkie wyświetlacze
        wlacz_wyswietlacz(0, 1, 1);
        wlacz_wyswietlacz(0, 2, 1);
        wlacz_wyswietlacz(0, 3, 1);
        wlacz_wyswietlacz(0, 4, 1);

        // Podziel liczbę przed przecinkiem na poszczególne cyfry i wyświetl na odpowiednich wyświetlaczach
        int digit = 0;
        int number = distance_int;
        int numer_wyswietlacza = 1; // Numer pierwszego wyświetlacza

        while (number > 0 && numer_wyswietlacza <= 4)
        {
            digit = number % 10;
            number /= 10;
            wlacz_wyswietlacz(digit, numer_wyswietlacza, 1);
            numer_wyswietlacza++;
        }

        // Przetwórz część po przecinku i wyświetl ją na odpowiednich wyświetlaczach
        number = fraction_int;
        numer_wyswietlacza = 1; // Numer pierwszego wyświetlacza dla części po przecinku

        while (number > 0 && numer_wyswietlacza <= 2) // Dla dwóch cyfr po przecinku
        {
            digit = number % 10;
            number /= 10;
            // wlacz_wyswietlacz(digit, numer_wyswietlacza + 2); // Wyświetlacz 3 i 4
            // numer_wyswietlacza++;
        }
    }

    odczytano = 0; // Zresetuj flagę odczytu
}
      }
wyswietlacz_liczba_jeden(0);
wyswietlacz_liczba_dwa(0);
wyswietlacz_liczba_trzy(0);
wyswietlacz_liczba_cztery(0);

        wyswietlacz_liczba_jeden(1);
        wyswietlacz_segment_a(1);
        wyswietlacz_segment_b(1);
        wyswietlacz_segment_c(1);
        wyswietlacz_segment_d(1);
        wyswietlacz_segment_e(1);
        wyswietlacz_segment_f(1);
        wyswietlacz_segment_g(1);
        wyswietlacz_liczba_jeden(0);

        wyswietlacz_liczba_dwa(1);
        wyswietlacz_segment_a(1);
        wyswietlacz_segment_b(1);
        wyswietlacz_segment_c(1);
        wyswietlacz_segment_d(1);
        wyswietlacz_segment_e(1);
        wyswietlacz_segment_f(1);
        wyswietlacz_segment_g(1);
        wyswietlacz_liczba_dwa(0);

        wyswietlacz_liczba_trzy(1);
        wyswietlacz_segment_a(1);
        wyswietlacz_segment_b(1);
        wyswietlacz_segment_c(1);
        wyswietlacz_segment_d(1);
        wyswietlacz_segment_e(1);
        wyswietlacz_segment_f(1);
        wyswietlacz_segment_g(1);
        wyswietlacz_liczba_trzy(0);

        wyswietlacz_liczba_cztery(1);
        wyswietlacz_segment_a(1);
        wyswietlacz_segment_b(1);
        wyswietlacz_segment_c(1);
        wyswietlacz_segment_d(1);
        wyswietlacz_segment_e(1);
        wyswietlacz_segment_f(1);
        wyswietlacz_segment_g(1);
        wyswietlacz_liczba_cztery(0);
    }
}


// TODO

//zrobić funkcje

//wlacz_wyswietlacz(jaka cyfra, jaki numer_wyswietlacza, wlacz/wylacz)
