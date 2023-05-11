#ifndef TIMERY
#define TIMERY

volatile extern uint8_t odczytano;
volatile extern float czas_powrotu_sygnalu_us;
volatile extern float odleglosc;

void timer1_init(void);
void delay_ms(int t);
void TIM1_UP_IRQHandler(void);
void TIM2_IRQHandler();
void couter_enable();

#endif /* TIMERY */
