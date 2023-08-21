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
}
