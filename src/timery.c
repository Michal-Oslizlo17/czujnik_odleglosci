#include "stm32f103xb.h" // Inicjalizacja zmiennej wskaźnika opóźnienia
#include "timery.h"

volatile int time;
volatile uint32_t delayVar; // Flagę, która będzie ustawiona na True, jeśli przycisk jest wciśnięty
volatile int liczba_tickow = 0;
volatile uint8_t odczytano = 0;
volatile float czas_powrotu_sygnalu_us = 0;
volatile float odleglosc_cm = 0;

// Funkcja inicjalizacji timera
void timer1_init(void)
{
    // Włącz zegar dla portu GPIOC i TIM1
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_TIM1EN;
    // Ustawienie flagi przerwania od "update"
    TIM1->DIER |= TIM_DIER_UIE;
    // Ustaw pre-scalar na 8kHz/80-100000
    TIM1->PSC = 8 - 1;
    // Ustaw wartość rejestru ARR na 100kHz/100-1kHz
    TIM1->ARR = 10 - 1;

    // Ustawienie tego zegara jest takie, by wlaczyl pik na 10us i sie wylaczyl
}

void SysTick_Handler() // SysTick
{
    if (time)
        time--;

    TIM1->CR1 |= TIM_CR1_CEN; // WLACZ LICZNIK
}
void delay_ms(int t) // Opóźnienie (ms)
{
    time = t;
    while (time)
        ;
}

// Funkcja obsługi przerwań dla timer1 - impuls wyzwalajacy odleglosciomierz
void TIM1_UP_IRQHandler(void)
{
    // Sprawdź, jaka sytuacja wywołała przerwanie
    if (TIM1->SR & TIM_SR_UIF)
    {
        if ((GPIOA->ODR & GPIO_ODR_ODR2))
            TIM1->CR1 &= ~TIM_CR1_CEN;      // wylacz licznik

        // Przełącz stan wyjścia PC14
        GPIOA->ODR ^= GPIO_ODR_ODR2;
        // Wyczyść flagę przerwania
        TIM1->SR &= ~TIM_SR_UIF;
        // Jeśli odliczanie jest większe od 0, zmniejsz go.
    }
}

void TIM2_IRQHandler()
{
    if (TIM2->SR && TIM_SR_CC1IF) // narastanie
    {
        TIM2->SR &= ~TIM_SR_CC1IF; // skasowanie tej flagi
        liczba_tickow = 0;
        odczytano = 0;
    }

    if (TIM2->SR && TIM_SR_CC2IF) // opadanie
    {
        TIM2->SR &= ~TIM_SR_CC2IF; // skasowanie tej flagi
        liczba_tickow = TIM2->CCR2 - TIM2->CCMR1;
        czas_powrotu_sygnalu_us = liczba_tickow / (float)8;
        odleglosc_cm = (czas_powrotu_sygnalu_us * 34) / 1000 / 2;

        odczytano = 1;
    }
}

void couter_enable()
{
    // PA0 in reset state, floating , input
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPAEN; // enable clock to C, Tim2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;                      // apb1 dziala na 8MHZ chyba
    TIM2->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_1;      // IC1 is mapped on TI1, IC2 is mapped on TI1
    TIM2->CCER &= ~TIM_CCER_CC1P;
    TIM2->CCER |= TIM_CCER_CC2P;                 // CC1 active rising, CC2 active falling
    TIM2->SMCR |= TIM_SMCR_TS_2 | TIM_SMCR_TS_0; // Trigger is TI1FP1
    TIM2->SMCR |= TIM_SMCR_SMS_2;                // Tim2 reset mode
    TIM2->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E; // enable capture

    TIM2->PSC = 0;     // prescaler TIM2 as 1
    TIM2->ARR = 65535; // Auto Reload = 65535

    TIM2->CR1 |= TIM_CR1_CEN; // counter enable

    // w tym przykładzie na PA1 wpuszczamy sygnał i debuggerem sprawdzamy do ilu doliczył
    // licznik od zbocza narastającego do narastającego (CCR1) i od zbocza narastającego do opadającego (CCR2)

    // dobrze byłoby wygenerowac przerwanie od zbocza opadajacego
    TIM2->DIER |= TIM_DIER_CC2IE | TIM_DIER_CC1IE;
}


// // Funkcja inicjalizacji przycisku
// void button_init(void)
// {
//     // Włącz zegar dla portu GPIOB
//     RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
//     // Ustaw pin 12 jako wyjście
//     GPIOB->CRH |= GPIO_CRH_MODE12_0;
//     // Ustaw pin 12 jako zwykłe wejście
//     GPIOB->CRH &= ~GPIO_CRH_CNF12_0;
//     // Ustaw stan logiczny na HIGH
//     GPIOB->ODR |= GPIO_ODR_ODR12;
// }