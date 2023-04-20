#ifndef UART
#define UART

// Funkcja odczytuje dane z interfejsu UART
void read_uart_data(void);
void uart_init();
void USART1_IRQHander(void);
void USART1_SendByte(uint8_t);

#endif /* UART */
