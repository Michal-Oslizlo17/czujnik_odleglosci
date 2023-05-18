#include "stm32f103xb.h" // Inicjalizacja zmiennej wskaźnika opóźnienia
#include "../include/configure_GPIO_inputs.h"

void configure_GPIO_inputs(void)
{
    // --------------------------- Tutaj robilem zmiany
    // Ustaw tryb wejścia i prędkość wejścia 2 MHz dla portów B3, B4, B5, B12, B13, B14, B15
    GPIOB->CRL |= GPIO_CRL_MODE3_1;
    GPIOB->CRL |= GPIO_CRL_MODE4_1;
    GPIOB->CRL |= GPIO_CRL_MODE5_1;
    GPIOB->CRH |= GPIO_CRH_MODE12_1;
    GPIOB->CRH |= GPIO_CRH_MODE13_1;
    GPIOB->CRH |= GPIO_CRH_MODE14_1;
    GPIOB->CRH |= GPIO_CRH_MODE15_1;

    GPIOB->CRL &= ~GPIO_CRL_CNF3;
    GPIOB->CRL &= ~GPIO_CRL_CNF4;
    GPIOB->CRL &= ~GPIO_CRL_CNF5;
    GPIOB->CRH &= ~GPIO_CRH_CNF12;
    GPIOB->CRH &= ~GPIO_CRH_CNF13;
    GPIOB->CRH &= ~GPIO_CRH_CNF14;
    GPIOB->CRH &= ~GPIO_CRH_CNF15;
    // ---------------------------

    // Ustaw pin PA1 jako wyjście
    GPIOA->CRL &= ~GPIO_CRL_CNF1_0;
    GPIOA->CRL |= GPIO_CRL_MODE1_1;

    // Ustaw pin PC13 jako wyjście
    GPIOC->CRH |= GPIO_CRH_MODE13_1;

    // Ustaw pin PC13 jako wejście
    GPIOC->CRH &= ~GPIO_CRH_CNF13_0;
}

void wyswietlacz_segment_a(uint8_t s)
{
    if (s == 1)
        GPIOB->ODR |= GPIO_ODR_ODR3;
    else if (s == 0)
        GPIOB->ODR &= ~GPIO_ODR_ODR3;
}

void wyswietlacz_segment_b(uint8_t s)
{
    if (s == 1)
        GPIOB->ODR |= GPIO_ODR_ODR4;
    else if (s == 0)
        GPIOB->ODR &= ~GPIO_ODR_ODR4;
}

void wyswietlacz_segment_c(uint8_t s)
{
    if (s == 1)
        GPIOB->ODR |= GPIO_ODR_ODR5;
    else if (s == 0)
        GPIOB->ODR &= ~GPIO_ODR_ODR5;
}

void wyswietlacz_d(uint8_t s)
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
    case 0:
        wyswietlacz_segment_prawo_gora(1);
        break;

    default:
        break;
    }
}