#include "stm32f103xb.h"    // Inicjalizacja zmiennej wskaźnika opóźnienia
volatile uint32_t delayVar; // Flagę, która będzie ustawiona na True, jeśli przycisk jest wciśnięty
volatile uint8_t isButtonPressed;
volatile int time;

void SysTick_Handler() // SysTick
{
    if (time)
        time--;

    TIM1->CR1 |= TIM_CR1_CEN;
}
void delay_ms(int t) // Opóźnienie (ms)
{
    time = t;
    while (time)
        ;
}

// Funkcja obsługi przerwań dla timer1
void TIM1_UP_IRQHandler(void)
{
    // Sprawdź, jaka sytuacja wywołała przerwanie
    if (TIM1->SR & TIM_SR_UIF)
    {
        if ((GPIOC->ODR & GPIO_ODR_ODR13))
            TIM1->CR1 &= ~TIM_CR1_CEN;

        // Przełącz stan wyjścia PC13
        GPIOC->ODR ^= GPIO_ODR_ODR13;
        // Wyczyść flagę przerwania
        TIM1->SR &= ~TIM_SR_UIF;
        // Jeśli odliczanie jest większe od 0, zmniejsz go.
    }
}

// Funkcja inicjalizacji timera
void timer_init(void)
{
    // Włącz zegar dla portu GPIOC i TIM1
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_TIM1EN;
    // Ustawienie flagi przerwania od "update"
    TIM1->DIER |= TIM_DIER_UIE;
    // Ustaw pre-scalar na 8kHz/80-100000
    TIM1->PSC = 8 - 1;
    // Ustaw wartość rejestru ARR na 100kHz/100-1kHz
    TIM1->ARR = 10 - 1;
    // Wyłącz timer1
    // TIM1->CR1 &= ~TIM_CR1_CEN;
    // TIM1->CR1 |= TIM_CR1_CEN;
}

// Funkcja inicjalizacji przycisku
void button_init(void)
{
    // Włącz zegar dla portu GPIOB
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    // Ustaw pin 12 jako wyjście
    GPIOB->CRH |= GPIO_CRH_MODE12_0;
    // Ustaw pin 12 jako zwykłe wejście
    GPIOB->CRH &= ~GPIO_CRH_CNF12_0;
    // Ustaw stan logiczny na HIGH
    GPIOB->ODR |= GPIO_ODR_ODR12;
}

void couter_enable() // nie wlacza sie
{
    // PA0 in reset state, floating , input
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPAEN | RCC_APB1ENR_TIM2EN; // enable clock to C, Tim2

    TIM2->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_1; // IC1 is mapped on TI1, IC2 is mapped on TI1
    TIM2->CCER &= ~TIM_CCER_CC1P;
    TIM2->CCER |= TIM_CCER_CC2P;                 // CC1 active rising, CC2 active falling
    TIM2->SMCR |= TIM_SMCR_TS_2 | TIM_SMCR_TS_0; // Trigger is TI1FP1
    TIM2->SMCR |= TIM_SMCR_SMS_2;                // Tim2 reset mode
    TIM2->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E; // enable capture

    TIM2->PSC = 0;     // prescaler TIM1 as 1
    TIM2->ARR = 65535; // Auto Reload = 65535

    TIM2->CR1 |= TIM_CR1_CEN; // counter enable
}

// Funkcja główna
int main(void)
{
    SysTick_Config(200000);                       // Domyślnie: SysTick_Config(8000);
    SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk; // 8000000/8

    // Inicjalizacja przycisku
    button_init();
    // Inicjalizacja timera
    timer_init();
    // Ustaw pin PC13 jako wyjście
    GPIOC->CRH |= GPIO_CRH_MODE13_1;
    // Ustaw pin PC13 jako wejście
    GPIOC->CRH &= ~GPIO_CRH_CNF13_0;
    // Włącz NVIC dla przerwań timera1
    NVIC_EnableIRQ(TIM1_UP_IRQn);

couter_enable();
    // Pętla główna
    while (1)
    {
        // // Jeśli stan logiczny pinu PB12 jest HIGH
        // if (GPIOB->IDR & GPIO_IDR_IDR12)
        // {
        //     GPIOC->ODR ^= GPIO_ODR_ODR13;
        //     // Ustaw flagę isButtonPressed na True
        //     isButtonPressed = 1;
        //     // Miejsce kodu do mrugania diodą
        // }

        // // Jeśli stan logiczny pinu PB12 jest LOW
        // else
        // {
        //     // Ustaw flagę isButtonPressed na False
        //     isButtonPressed = 0;
        // }
    }
}