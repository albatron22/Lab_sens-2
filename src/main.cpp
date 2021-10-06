#include <Arduino.h>
#include "LCD_Driver.h"

uint32_t period = 0;      // период сигнала, мкс
uint32_t t_us = 0;        // вспомогательная метка времени
uint32_t pulse_count = 0; // счётчик импульсов с датчика
uint32_t freq = 0;        // частота сигнала, Гц

char msg[64] = {'\0'};

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
    //LCD_SendString("Init", strlen("Init"));
}

void loop()
{
    period = micros() - t_us;
    if (period >= 200000) // 200 ms
    {
        cli();
        //freq = (float)pulse_count / (float)period * 1e6f;
        freq = (pulse_count * (uint32_t)1e6) / period;
        pulse_count = 0;
        t_us = micros();
        sei();
        LCD_Clear();
        LCD_GotoXY(0, 0);
        LCD_SendString("Hz", strlen("Hz"));
        LCD_GotoXY(0, 1);
        sprintf(msg, "%ld", freq);
        LCD_SendString(msg, strlen(msg));
    }
}

/**
 * @brief Call-back функция обработчика прерывания по сигналу в выхода датчика
 * Инкрементирование счётчика импульсов.
*/
void color_sens_out()
{
    pulse_count++;
}