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

int main(void)
{
    SysTick_Config(2 * 8000000 / 8);
    // SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;

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

    int liczba[4];
    // Pętla główna
    while (1)
    {
        wylacz_wszystkie_wyswietlacze();
        // Jeśli odczytano dane, przetwórz je i wyświetl na wyświetlaczach
        if (odczytano == 1)
        {
            // ftoa(odleglosc_cm, wynik_cstring, 2);
            //intToStr((int)odleglosc_cm, wynik_cstring, 4);
            intToStr(12, wynik_cstring, 4);

            // Testowo wyrzucamy do USART. Przyda się do aplikacji
            USART1_SendCString(wynik_cstring, 10);
            USART1_SendByte('\n');

            // Dalej zajmiemy się tylko czescia calkowita
            // TODO - nie dziala wyswietlanie - do przerobienia 
            // Trzeba zrobic funkcje dla kazdego wyswietlacza
            // np. wyswietlacz1(liczba, on/off)
            
            liczba[0] = wynik_cstring[0] - 48;
            liczba[1] = wynik_cstring[1] - 48;
            liczba[2] = wynik_cstring[2] - 48;
            liczba[3] = wynik_cstring[3] - 48;


            wlacz_wyswietlacz(liczba[0], 1, 1);
            wlacz_wyswietlacz(liczba[1], 2, 1);
            wlacz_wyswietlacz(liczba[2], 3, 1);
            wlacz_wyswietlacz(liczba[3], 4, 1);

            odczytano = 0;
        }
    }
}

// TODO

// zrobić funkcje

// wlacz_wyswietlacz(jaka cyfra, jaki numer_wyswietlacza, wlacz/wylacz)
