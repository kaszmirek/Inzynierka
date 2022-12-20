#include "stdio.h"
#include "string.h"
#include "comunication.h"
#include "serial.h"
#include "retarget.h"
#include "dac.h"
#include "tim.h"

#include "global_variables.h"

#define CHANNELS_NUM 3
#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

char buff[20];
int cmdID, param;
int pulse_count;
uint8_t buff_size = 0;

enum Cmd
{
    START,
    TEST_PIEZO,
    REPS,
    PWM,
    THR,
    WAIT
};

void MsgHandler()
{
    if (get_ready_to_send())
        SendResults();

    if (serial_available())
    {
        uint8_t c = serial_read();
        buff[buff_size] = c;
        buff_size++;
        if (c == '\n')
        {
            printf("Captured MSG: %s", buff);
            if (buff[0] == 'X' && sscanf(buff + 2, "%d %d", &cmdID, &param) == 2)
            {
                printf("MSG CmdId: %d, Param: %d \r\n", cmdID, param);
                ExecCmd(cmdID, param);
            }
            else
                printf("ERROR: MSG INVALID\r\n");
            memset(buff, 0, sizeof buff);
            buff_size = 0;
        }
    }
}

void ExecCmd(int _cmd, int _param)
{
    switch (_cmd)
    {
    case START:
        // reset all timers
        TIM16->CR1 |= TIM_CR1_CEN;
        printf("Measure started\r\n");
        break;
    case TEST_PIEZO:
        SendResults();
        printf("Test send\r\n");
        // start timer
        break;
    case REPS:
        // htim16.Init.RepetitionCounter = constrain(_param, 0, 10);
        TIM16->RCR = constrain(_param, 0, 10) - 1;
        printf("Number of PWM reps changed to %d\r\n", _param);
        break;
    case PWM:
        TIM16->CCR1 = constrain(_param, 0, 199);
        printf("PWM fill changed to %d %%\r\n", _param);
        break;
    case THR:
        HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, constrain(_param, 0, 4095)); // todo: global thr value
        printf("THR changed to %d\r\n", _param);
        break;
    case WAIT:
        // SetWaitTime();
        printf("Wait time changed to %d\r\n", _param);
        break;
    default:
        printf("ERROR cmdId: %d is unknown\r\n", _cmd);
        break;
    }
}

void SendResults()
{
    printf("Y 1 %c ", get_zero_cross(0));

    for (uint8_t i = 0; i < CHANNELS_NUM; i++)
    {
        for (uint8_t j = 0; i < get_pulse_count(); i++)
        {
            printf("%ld ", get_timing_array(i, j));
        }
    }
    printf("\r\n");
}