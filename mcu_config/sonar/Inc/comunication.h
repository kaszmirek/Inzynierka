#ifndef _COMUNICATION_H__
#define _COMUNICATION_H__

#include "stm32l4xx_hal.h"

void MsgHandler();
void ExecCmd(int, int);
void SendResults();

#endif