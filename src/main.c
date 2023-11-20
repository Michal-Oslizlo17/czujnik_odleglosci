#include "stm32f103xb.h"
#include "timery.h"
#include "uart.h"
#include "ftoa.h"
#include <string.h>
#include "../include/configure_GPIO.h"
#include "../include/wyswietlacze.h"

volatile uint8_t isButtonPressed;
#define BUFFER_SIZE 64
char buffer[BUFFER_SIZE];
int buffer_index = 0;

#define DISPLAY_PERIOD 50

int main(void)
{
    SysTick_Config(8000000 / 8000);

    timer1_init();
    timer3_init();
    couter_enable();

    // Włącz NVIC dla przerwań timera1
    NVIC_EnableIRQ(TIM1_UP_IRQn);
    NVIC_EnableIRQ(TIM3_IRQn);
    NVIC_EnableIRQ(TIM2_IRQn);
    uart_init();

    // Konfiguracja portów
    configure_GPIO();

    
    char wynik_cstring[10];

    int liczba[4];
    // Pętla główna
    while (1)
    {
        wylacz_wszystkie_wyswietlacze();

        intToStr((int)odleglosc_cm, wynik_cstring, 4);

        USART1_SendCString(wynik_cstring, 10);
        USART1_SendByte('\n');

// Działa. Wymyśl proszę, aby gdy uklad zmierzy np. 12 cm NIE wyswietlalo sie 0012 tylko samo 12
// bez swiecacych dwoch przednich wyswietlaczy. A gdy znow naa przykład zmierzy 132 to nie pokaże
// się 0132 tylko samo 132. 

// Generalnie można pierwszy wyświetlacza wyrzucić programowo, bo czujnik mierzy do 200cm
// więc nie ma sensu. Wystarczy do 199. Czyli pierwszy wyswietlacz do wywalenia.

        liczba[0] = wynik_cstring[0] - 48;
        liczba[1] = wynik_cstring[1] - 48;
        liczba[2] = wynik_cstring[2] - 48;
        liczba[3] = wynik_cstring[3] - 48;

        wlacz_wyswietlacz(liczba[0], 1, 1);
        delay_ms(DISPLAY_PERIOD);
        wlacz_wyswietlacz(0, 1, 0);
        wlacz_wyswietlacz(liczba[1], 2, 1);
        delay_ms(DISPLAY_PERIOD);
        wlacz_wyswietlacz(0, 2, 0);
        wlacz_wyswietlacz(liczba[2], 3, 1);
        delay_ms(DISPLAY_PERIOD);
        wlacz_wyswietlacz(0, 3, 0);
        wlacz_wyswietlacz(liczba[3], 4, 1);
        delay_ms(DISPLAY_PERIOD);
        wlacz_wyswietlacz(0, 4, 0);

        odczytano = 0;
    }
}


