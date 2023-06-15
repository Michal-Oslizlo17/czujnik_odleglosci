#include "stm32f103xb.h" // Inicjalizacja zmiennej wskaźnika opóźnienia
#include "../include/configure_GPIO_inputs.h"

void configure_GPIO_inputs(void)
{
     RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
     RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
     RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // --------------------------- Tutaj robilem zmiany
    // Ustaw tryb wejścia i prędkość wejścia 2 MHz dla portów B3, B4, B5, B12, B13, B14, B15
    GPIOB->CRH |= GPIO_CRH_MODE11_1;
    GPIOB->CRH |= GPIO_CRH_MODE10_1;
    GPIOB->CRL |= GPIO_CRL_MODE5_1;
    GPIOB->CRH |= GPIO_CRH_MODE12_1;
    GPIOB->CRH |= GPIO_CRH_MODE13_1;
    GPIOB->CRH |= GPIO_CRH_MODE14_1;
    GPIOB->CRH |= GPIO_CRH_MODE15_1;

    GPIOB->CRH &= ~GPIO_CRH_CNF11_0; //
    GPIOB->CRH &= ~GPIO_CRH_CNF10_0;
    GPIOB->CRL &= ~GPIO_CRL_CNF5_0;
    GPIOB->CRH &= ~GPIO_CRH_CNF12_0;
    GPIOB->CRH &= ~GPIO_CRH_CNF13_0;
    GPIOB->CRH &= ~GPIO_CRH_CNF14_0;
    GPIOB->CRH &= ~GPIO_CRH_CNF15_0;
    // ---------------------------

    // Ustaw pin PA1 jako wyjście
    GPIOA->CRL &= ~GPIO_CRL_CNF1_0;
    GPIOA->CRL |= GPIO_CRL_MODE1_1;

    // Ustaw pin PC13 jako wyjście
    GPIOC->CRH |= GPIO_CRH_MODE13_1;

    //*********************************************
    // WLACZANIE CYFR - konfiguracja pinow
    // Ustaw pin PB6 jako wyjście - Cyfra 1
    GPIOB->CRL &= ~GPIO_CRL_CNF6_0;
    GPIOB->CRL |= GPIO_CRL_MODE6_1;

    // Ustaw pin PB7 jako wyjście - Cyfra 2
    GPIOB->CRL &= ~GPIO_CRL_CNF7_0;
    GPIOB->CRL |= GPIO_CRL_MODE7_1;

    // Ustaw pin PB8 jako wyjście - Cyfra 3
    GPIOB->CRH &= ~GPIO_CRH_CNF8_0;
    GPIOB->CRH |= GPIO_CRH_MODE8_1;

    // Ustaw pin PB9 jako wyjście - Cyfra 4
    GPIOB->CRH &= ~GPIO_CRH_CNF9_0;
    GPIOB->CRH |= GPIO_CRH_MODE9_1;
}

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
        wyswietlacz_segment_d(0);
        wyswietlacz_segment_e(1);
        wyswietlacz_segment_f(0);
        wyswietlacz_segment_g(1);
        break;

    case 4:
        wyswietlacz_segment_a(0);
        wyswietlacz_segment_b(0);
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