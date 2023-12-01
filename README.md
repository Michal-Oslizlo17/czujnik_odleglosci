# czujnik_odleglosci
Krótki opis projektu:
Jest to projekt dla mikrokontrolera STM32F103 i czujnika odległości.

# Projekt: Czujnik Odległości z Mikrokontrolerem STM32F103

## Opis
Projekt ma na celu zastosowanie mikrokontrolera STM32F103 w celu precyzyjnego pomiaru odległości przy wykorzystaniu czujnika odległości.
Mikrokontroler kontroluje cały proces pomiaru, przetwarzania danych i prezentacji wyników na segmentowych wyświetlaczach LED.

## Komponenty Projektu

### Mikrokontroler STM32F103
- **Opis:** STM32F103 to zaawansowany mikrokontroler z rodziny STM32, oparty na rdzeniu ARM Cortex-M3. Posiada różnorodne interfejsy, takie jak GPIO, SPI, I2C, UART, co umożliwia szerokie zastosowanie w projektach wbudowanych.
- **Funkcje w Projekcie:**
    - Konfiguracja portów GPIO do obsługi czujnika odległości i wyświetlaczy LED.
    - Inicjalizacja timerów do generowania przerwań i opóźnień.
    - Konfiguracja modułu UART do komunikacji z zewnętrznymi urządzeniami oraz do debugowania.

### Czujnik Odległości
- **Opis:** Wykorzystamy ultradźwiękowy czujnik odległości. Tego typu czujnik mierzy czas podróży fali dźwiękowej do obiektu i z powrotem, umożliwiając precyzyjny pomiar odległości.
- **Funkcje w Projekcie:**
    - Pomiar odległości do obiektu.
    - Przetworzenie danych pomiarowych na wartość liczbową.

### Wyświetlacze LED Segmentowe
- **Opis:** Segmentowe wyświetlacze LED służą do prezentacji wyników pomiarów w formie cyfrowej.
- **Funkcje w Projekcie:**
    - Wyświetlanie wyników pomiaru odległości w formie cyfrowej.

## Koncepcja Działania
1. Inicjalizacja mikrokontrolera STM32F103, timerów, modułu UART, portów GPIO, czujnika odległości i wyświetlaczy LED.
2. Pomiar odległości za pomocą *ultradźwiękowego* czujnika odległości.
3. Konwersja wyniku pomiaru na ciąg znaków.
4. Wyświetlanie wyniku na segmentowych wyświetlaczach LED.
5. Przekazywanie danych do komputera lub innego urządzenia za pomocą modułu *UART* w celu monitorowania i debugowania.
6. Wprowadzenie odpowiednich warunków i algorytmów, aby obsłużyć sytuacje szczególne, na przykład wykrywanie braku obiektu w zasięgu czujnika.
7. Powtarzanie procesu w pętli nieskończonej.

## Autorzy
Michał Oślizło,
Krzysztof Krupa.
