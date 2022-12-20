// wywołaj tą funkcje na każdym przerwaniu i dodaj wartość licznika do bufora
#include "stm32l4xx_hal.h"
#include "comunication.h"
#include "dac.h"
#include "tim.h"
#include "global_variables.h"
#include "serial.h"
#include "stdbool.h"
#include "stdio.h"
#include "usart.h"

int zero_cross[3] = {0};
uint32_t timing_array[][3] = {0};
int send_flag = false;
uint8_t active_channel = 0;
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM16)
    {
        HAL_GPIO_TogglePin(DBG_LED_GPIO_Port, DBG_LED_Pin);
        TIM5->CR1 |= TIM_CR1_CEN;
        TIM6->CR1 |= TIM_CR1_CEN;
    }
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

    if (htim->Instance == TIM6) // wait
    {
        HAL_GPIO_TogglePin(DBG_LED_GPIO_Port, DBG_LED_Pin);
        HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
        HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
        HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);
        __HAL_TIM_SET_COUNTER(htim, 0);
    }
    else if (htim->Instance == TIM5) // timeout
    {
        HAL_TIM_IC_Stop_IT(&htim2, TIM_CHANNEL_1);
        HAL_TIM_IC_Stop_IT(&htim2, TIM_CHANNEL_2);
        HAL_TIM_IC_Stop_IT(&htim2, TIM_CHANNEL_3);
        set_ready_to_send(true);
        __HAL_TIM_SET_COUNTER(htim, 0);
    }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    switch (htim->Channel)
    {
    case HAL_TIM_ACTIVE_CHANNEL_1:
        active_channel = 1 - 1;
        zero_cross[0]++;
        set_timing_array(1, zero_cross[0], HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1));
        break;
    case HAL_TIM_ACTIVE_CHANNEL_2:
        active_channel = 2 - 1;
        zero_cross[1]++;
        set_timing_array(1, zero_cross[1], HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2));
        break;
    case HAL_TIM_ACTIVE_CHANNEL_3:
        active_channel = 3 - 1;
        zero_cross[2]++;
        set_timing_array(1, zero_cross[2], HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3));
        break;
    default:
        break;
    }
}
