#include "stm32f103xb.h"

void read_uart_data(void)
{
    // Sprawdź, czy wystąpiło przerwanie w interfejsie USART1 związane z odebraniem danych
    if (USART1->SR & USART_SR_RXNE)
    {
        // Odczytaj odebrane dane z rejestru DR
        char received_data = USART1->DR;

        // Tutaj można dodać kod, który będzie przetwarzał odebrane dane
        // np. zapisując je do bufora lub wywołując inną funkcję w celu ich przetworzenia
    }
}

void uart_init()
{
    // Init
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRH |= GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_0;
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
    // PA10 wejście (pływające)
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // Command
    USART1->CR1 |= USART_CR1_UE;
    USART1->CR1 |= USART_CR1_RXNEIE;
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;
    USART1->BRR = (8000000 / 9600);
}