// wywołaj tą funkcje na każdym przerwaniu i dodaj wartość licznika do bufora

#include "measure.h"

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
        if (Is_First_Captured == 0) // if the first rising edge is not captured
        {
            IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read the first value
            Is_First_Captured = 1;                                    // set the first captured as true
            ChangeThereshold(thereshold);
        }

        else // If the first rising edge is captured, now we will capture the second edge
        {
            IC_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read second value

            __HAL_TIM_SET_COUNTER(htim, 0); // reset the counter
            Is_First_Captured = 0;          // set it back to false
        }
    }
}

void ChangeThereshold(int thr)
{
    HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 3000);
}

