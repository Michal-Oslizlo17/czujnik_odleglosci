#include "stm32f103xb.h" // Inicjalizacja zmiennej wskaźnika opóźnienia
#include "timery.h"
#include <string.h>
volatile uint8_t isButtonPressed;


#define BUFFER_SIZE 64
char buffer[BUFFER_SIZE];
int buffer_index = 0;



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





// Funkcja główna
int main(void)
{
    SysTick_Config(200000);                       // Domyślnie: SysTick_Config(8000);
    SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk; // 8000000/8

    // Inicjalizacja przycisku
    button_init();
    // Inicjalizacja timera
    timer1_init();
    // Ustaw pin PC13 jako wyjście
    GPIOC->CRH |= GPIO_CRH_MODE13_1;
    // Ustaw pin PC13 jako wejście
    GPIOC->CRH &= ~GPIO_CRH_CNF13_0;
    // Włącz NVIC dla przerwań timera1
    NVIC_EnableIRQ(TIM1_UP_IRQn);
    NVIC_EnableIRQ(TIM2_IRQn);

    couter_enable();

    // Pętla główna
    while (1)
    {
    }
}