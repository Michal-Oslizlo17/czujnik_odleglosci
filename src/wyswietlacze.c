#include "stm32f103xb.h" // Inicjalizacja zmiennej wskaźnika opóźnienia
#include "../include/configure_GPIO_inputs.h"

// CYFRY
void wyswietlacz_liczba_jeden(uint8_t s)
{
    if (s == 0)
        GPIOB->ODR |= GPIO_ODR_ODR6;
    else if (s == 1)
        GPIOB->ODR &= ~GPIO_ODR_ODR6;
}

void wyswietlacz_liczba_dwa(uint8_t s)
{
    if (s == 0)
        GPIOB->ODR |= GPIO_ODR_ODR7;
    else if (s == 1)
        GPIOB->ODR &= ~GPIO_ODR_ODR7;
}

void wyswietlacz_liczba_trzy(uint8_t s)
{
    if (s == 0)
        GPIOB->ODR |= GPIO_ODR_ODR8;
    else if (s == 1)
        GPIOB->ODR &= ~GPIO_ODR_ODR8;
}

void wyswietlacz_liczba_cztery(uint8_t s)
{
    if (s == 0)
        GPIOB->ODR |= GPIO_ODR_ODR9;
    else if (s == 1)
        GPIOB->ODR &= ~GPIO_ODR_ODR9;
}

// SEGMENTY
void wyswietlacz_segment_a(uint8_t s)
{
    if (s == 1)
        GPIOB->ODR |= GPIO_ODR_ODR11;
    else if (s == 0)
        GPIOB->ODR &= ~GPIO_ODR_ODR11;
}

void wyswietlacz_segment_b(uint8_t s)
{
    if (s == 1)
        GPIOB->ODR |= GPIO_ODR_ODR10;
    else if (s == 0)
        GPIOB->ODR &= ~GPIO_ODR_ODR10;
}

void wyswietlacz_segment_c(uint8_t s)
{
    if (s == 1)
        GPIOB->ODR |= GPIO_ODR_ODR5;
    else if (s == 0)
        GPIOB->ODR &= ~GPIO_ODR_ODR5;
}

void wyswietlacz_segment_d(uint8_t s)
{
    if (s == 1)
        GPIOB->ODR |= GPIO_ODR_ODR12;
    else if (s == 0)
        GPIOB->ODR &= ~GPIO_ODR_ODR12;
}

void wyswietlacz_segment_e(uint8_t s)
{
    if (s == 1)
        GPIOB->ODR |= GPIO_ODR_ODR13;
    else if (s == 0)
        GPIOB->ODR &= ~GPIO_ODR_ODR13;
}

void wyswietlacz_segment_f(uint8_t s)
{
    if (s == 1)
        GPIOB->ODR |= GPIO_ODR_ODR14;
    else if (s == 0)
        GPIOB->ODR &= ~GPIO_ODR_ODR14;
}

void wyswietlacz_segment_g(uint8_t s)
{
    if (s == 1)
        GPIOB->ODR |= GPIO_ODR_ODR15;
    else if (s == 0)
        GPIOB->ODR &= ~GPIO_ODR_ODR15;
}

void wyswietlacz_segment_on_off(uint8_t liczba)
{
    switch (liczba)
    {
    case 1:
        wyswietlacz_segment_a(0);
        wyswietlacz_segment_b(1);
        wyswietlacz_segment_c(1);
        wyswietlacz_segment_d(0);
        wyswietlacz_segment_e(0);
        wyswietlacz_segment_f(0);
        wyswietlacz_segment_g(0);
        break;

    case 2:
        wyswietlacz_segment_a(1);
        wyswietlacz_segment_b(1);
        wyswietlacz_segment_c(0);
        wyswietlacz_segment_d(1);
        wyswietlacz_segment_e(1);
        wyswietlacz_segment_f(0);
        wyswietlacz_segment_g(1);
        break;

    case 3:
        wyswietlacz_segment_a(1);
        wyswietlacz_segment_b(1);
        wyswietlacz_segment_c(1);
        wyswietlacz_segment_d(1);
        wyswietlacz_segment_e(0);
        wyswietlacz_segment_f(0);
        wyswietlacz_segment_g(1);
        break;

    case 4:
        wyswietlacz_segment_a(0);
        wyswietlacz_segment_b(1);
        wyswietlacz_segment_c(1);
        wyswietlacz_segment_d(0);
        wyswietlacz_segment_e(0);
        wyswietlacz_segment_f(1);
        wyswietlacz_segment_g(1);
        break;

    case 5:
        wyswietlacz_segment_a(1);
        wyswietlacz_segment_b(0);
        wyswietlacz_segment_c(1);
        wyswietlacz_segment_d(1);
        wyswietlacz_segment_e(0);
        wyswietlacz_segment_f(1);
        wyswietlacz_segment_g(1);
        break;

    case 6:
        wyswietlacz_segment_a(1);
        wyswietlacz_segment_b(0);
        wyswietlacz_segment_c(1);
        wyswietlacz_segment_d(1);
        wyswietlacz_segment_e(1);
        wyswietlacz_segment_f(1);
        wyswietlacz_segment_g(1);
        break;

    case 7:
        wyswietlacz_segment_a(1);
        wyswietlacz_segment_b(1);
        wyswietlacz_segment_c(1);
        wyswietlacz_segment_d(0);
        wyswietlacz_segment_e(0);
        wyswietlacz_segment_f(0);
        wyswietlacz_segment_g(0);
        break;

    case 8:
        wyswietlacz_segment_a(1);
        wyswietlacz_segment_b(1);
        wyswietlacz_segment_c(1);
        wyswietlacz_segment_d(1);
        wyswietlacz_segment_e(1);
        wyswietlacz_segment_f(1);
        wyswietlacz_segment_g(1);
        break;

    case 9:
        wyswietlacz_segment_a(1);
        wyswietlacz_segment_b(1);
        wyswietlacz_segment_c(1);
        wyswietlacz_segment_d(1);
        wyswietlacz_segment_e(0);
        wyswietlacz_segment_f(1);
        wyswietlacz_segment_g(1);
        break;

    case 0:
        wyswietlacz_segment_a(1);
        wyswietlacz_segment_b(1);
        wyswietlacz_segment_c(1);
        wyswietlacz_segment_d(1);
        wyswietlacz_segment_e(1);
        wyswietlacz_segment_f(1);
        wyswietlacz_segment_g(0);
        break;

    default:
        break;
    }
}

void wylacz_wszystkie_wyswietlacze()
{
    // Wygasza wszystkie wysweietlacze
    wyswietlacz_liczba_jeden(0);
    wyswietlacz_liczba_dwa(0);
    wyswietlacz_liczba_trzy(0);
    wyswietlacz_liczba_cztery(0);
}

/**
 * @brief
 *
 * @param jaka_cyfra
 * @param numer_wyswietlacza
 * @param wlacz
 */
void wlacz_wyswietlacz(uint8_t jaka_cyfra, uint8_t numer_wyswietlacza, uint8_t wlacz)
{
    if (jaka_cyfra >= 0 && jaka_cyfra <= 9)
    {

        switch (numer_wyswietlacza)
        {
        case 1:
            wyswietlacz_liczba_jeden(wlacz == 0 ? 0 : 1);
            break;
        case 2:
            wyswietlacz_liczba_dwa(wlacz == 0 ? 0 : 1);
            break;
        case 3:
            wyswietlacz_liczba_trzy(wlacz == 0 ? 0 : 1);
            break;
        case 4:
            wyswietlacz_liczba_cztery(wlacz == 0 ? 0 : 1);
            break;
        default:
            break;
        }

        if (wlacz)
        {
            wyswietlacz_segment_on_off(jaka_cyfra);
        }
        else
        {
            // Wyłącz wszystkie segmenty
            wyswietlacz_segment_a(0);
            wyswietlacz_segment_b(0);
            wyswietlacz_segment_c(0);
            wyswietlacz_segment_d(0);
            wyswietlacz_segment_e(0);
            wyswietlacz_segment_f(0);
            wyswietlacz_segment_g(0);
        }
    }
}
