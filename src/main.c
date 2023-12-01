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
        // Komentarz: Chyba raczej działa, nie mam jak sprawdzić. Przepraszam. ~Michał

        // Stary kod (dla backupu):
        // ----------------------------------
        // liczba[0] = wynik_cstring[0] - 48;
        // liczba[1] = wynik_cstring[1] - 48;
        // liczba[2] = wynik_cstring[2] - 48;
        // liczba[3] = wynik_cstring[3] - 48;

        // wlacz_wyswietlacz(liczba[0], 1, 1);
        // delay_ms(DISPLAY_PERIOD);
        // wlacz_wyswietlacz(0, 1, 0);
        // wlacz_wyswietlacz(liczba[1], 2, 1);
        // delay_ms(DISPLAY_PERIOD);
        // wlacz_wyswietlacz(0, 2, 0);
        // wlacz_wyswietlacz(liczba[2], 3, 1);
        // delay_ms(DISPLAY_PERIOD);
        // wlacz_wyswietlacz(0, 3, 0);
        // wlacz_wyswietlacz(liczba[3], 4, 1);
        // delay_ms(DISPLAY_PERIOD);
        // wlacz_wyswietlacz(0, 4, 0);
        // ----------------------------------

        // Wyodrębnianie cyfr z ciągu znaków bez zer wiodących
        liczba[0] = (wynik_cstring[0] != '0') ? (wynik_cstring[0] - '0') : -1;
        liczba[1] = (wynik_cstring[1] != '0' || liczba[0] != -1 || (wynik_cstring[2] == '0' && wynik_cstring[3] == '0')) ? (wynik_cstring[1] - '0') : -1;
        liczba[2] = (wynik_cstring[2] != '0' || liczba[1] != -1 || wynik_cstring[3] == '0') ? (wynik_cstring[2] - '0') : -1;
        liczba[3] = wynik_cstring[3] - '0';

        // Wyświetlanie cyfr na odpowiednich segmentach
        if (liczba[0] != -1) {
            wlacz_wyswietlacz(liczba[0], 1, 1);
            delay_ms(DISPLAY_PERIOD);
            wlacz_wyswietlacz(0, 1, 0);
        }
        if (liczba[1] != -1) {
            wlacz_wyswietlacz(liczba[1], 2, 1);
            delay_ms(DISPLAY_PERIOD);
            wlacz_wyswietlacz(0, 2, 0);
        }
        if (liczba[2] != -1) {
            wlacz_wyswietlacz(liczba[2], 3, 1);
            delay_ms(DISPLAY_PERIOD);
            wlacz_wyswietlacz(0, 3, 0);
        }
        wlacz_wyswietlacz(liczba[3], 4, 1);
        delay_ms(DISPLAY_PERIOD);
        wlacz_wyswietlacz(0, 4, 0);

        // Wytłumaczenie działa za pamięci:
        /*
        - Wyodrębnianie cyfr bez zer wiodących:
        liczba[0]: Patrzymy na pierwszą cyfrę w wynik_cstring. Jeśli nie jest to zero, to przypisujemy jej wartość do liczba[0].
        Jeśli jednak pierwsza cyfra to zero, ustawiamy liczba[0] na -1, co sygnalizuje, że ta cyfra powinna zostać pominięta.
        
        liczba[1]: Podobnie jak wyżej, ale dodatkowo sprawdzamy, czy druga cyfra nie jest zerem, lub czy pierwsza cyfra nie była zerem,
        lub czy obie dwie ostatnie cyfry są zerami. Jeśli którykolwiek z tych warunków jest spełniony, przypisujemy wartość drugiej cyfry do liczba[1].
        W przeciwnym razie ustawiamy liczba[1] na -1.
        
        liczba[2]: Podobnie jak powyżej, ale dodatkowo sprawdzamy, czy trzecia cyfra nie jest zerem, lub czy druga cyfra nie była zerem,
        lub czy ostatnia cyfra jest zerem. Jeśli którykolwiek z tych warunków jest spełniony, przypisujemy wartość trzeciej cyfry do liczba[2].
        W przeciwnym razie ustawiamy liczba[2] na -1.
        
        liczba[3]: Przypisujemy wartość ostatniej cyfry do liczba[3].
        
        - Wyświetlanie cyfr:
        Dla każdej cyfry, sprawdzamy, czy jej wartość nie jest równa -1. Jeśli tak, to oznacza, że ta cyfra nie powinna być pominięta, więc włączamy odpowiedni segment na wyświetlaczu, stosujemy krótkie opóźnienie, a następnie wyłączamy segment. Procedurę tę powtarzamy dla każdej z czterech cyfr.
        Wartość -1 dla danej cyfry oznacza, że ta cyfra ma zostać pominięta, co eliminuje efekt zer wiodących.

        - Nie jestem pewny czy nie przypisuję wartości na odwrót to znaczy od lewej do prawej, a nie od prawej do lewej.
        */

        // Reset
        odczytano = 0;
    }
}
