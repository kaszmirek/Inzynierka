#include "comunication.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    if (UART2_rxBuffer[0] == "X") // pass only msg with "X" at the begining
        msg_flag = true;
}

void MsgHandler(uint8_t *buffer[])
{
    if (msg_flag) // if correct msg received
    {
        msg_flag = false;
        if (SetPulsesCount /*&& */ )
        {
            /* code */
        }
        
        SetPulsesCount();
        GeneratePulses(); 
        StartTimers(); // wait for pulses to end, timeout, start input capture

        int pulseCount = &buffer[3];
        htim16.Init.RepetitionCounter = pulseCount;
        HAL_TIM_OnePulse_Start_IT(&htim16, TIM_CHANNEL_1);
    }
    return;
}