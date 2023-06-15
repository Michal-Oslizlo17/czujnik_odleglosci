// 2023-03-09 14:32:04.162169
// Kod zmodyfikowany przez sieci neuronowe SarahAI.
// Wersja: 1.0.0
// Sieci neuronowe nadal uczą się różnych języków programowania,
// jeśli chcesz dowiedzieć się więcej to wejdź na githuba VermiNew.
// -------> Twój zmodyfikowany kod:

// Funkcja, która uruchamia timer, gdy jest stan wysoki na PC13 i sprawdza, czy stan niski jest wystarczający, aby zatrzymać timer
void timerCheck(void) 
{
    // Sprawdź, czy stan logiczny pinu PC13 jest wysoki
    if (GPIOC->ODR & GPIO_ODR_ODR13) 
    {
        // Włącz timer 1
        TIM1->CR1 |= TIM_CR1_CEN;

        // Sprawdź, czy stan logiczny pinu PC13 jest niski
        if (!(GPIOC->ODR & GPIO_ODR_ODR13))
        {
            // Wyłącz timer 1
            TIM1->CR1 &= ~TIM_CR1_CEN;
        }
    }
}
