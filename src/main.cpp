#include <Arduino.h>
#include "LCD_Driver.h"

uint32_t period = 0;      // период сигнала, мкс
uint32_t pulse_count = 0; // счётчик импульсов с датчика
float freq = 0.0f;        // частота сигнала, Гц

void color_sens_out();

void setup()
{
    /**
     * Настройка внешнего прерывания для считывания выходной частоты датчика.
     * Настройка на прерывание по восходящему фронту. 
     * Выходной сигнал датчика цвета (TCS3200) - 
     * меандр с частотой прямо пропорциональной интенсивность падающего света. 
    */
    attachInterrupt(EXTERNAL_INT_0, color_sens_out, RISING);

    /* Инициализация LCD-дисплея */
    LCD_Init();
    LCD_Clear();
    LCD_GotoXY(0, 0);
}

void loop()
{
}

/**
 * @brief Call-back функция обработчика прерывания по сигналу в выхода датчика
 * Инкрементирование счётчика импульсов.
*/
void color_sens_out()
{
    pulse_count++;
}