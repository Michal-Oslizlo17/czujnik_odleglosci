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

void uart_init() // TX - PA9, RX - PA10
{
    // Init
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRH |= GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1;
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
    // PA10 wejście (pływające)
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // Command
    USART1->CR1 |= USART_CR1_UE;
    USART1->CR1 |= USART_CR1_RXNEIE;
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;
    USART1->BRR = (8000000 / 9600);
}

void USART1_IRQHander(void)
{
    if (USART1->SR & USART_SR_RXNE)
    {
        USART1->SR &= ~USART_SR_RXNE;
    }

    char received_data = USART1->DR;
}

void USART1_SendByte(uint8_t d)
{
    // while (!(USART1->SR && USART_SR_TC));
    while (!(USART1->SR & USART_SR_TC));

    USART1->DR = d;
}

void USART1_SendCString(char *cs, int n)
{
    int i = 0;
    while (cs[i] != 0)
    {
        USART1_SendByte((uint8_t)cs[i]);
        i++;
    }

    // Jak tu wyczyścisz przez wskaźnik to potem w stringu same zera i dalej nic z nim nie zrobisz - dywersja jakas :)
    // for (uint8_t i = 0; i < 10; i++)
    // {
    //     cs[i] = 0;
    // }
}