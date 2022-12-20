#include "stm32l4xx_hal.h"

#include "main.h"
#include "serial.h"

UART_HandleTypeDef *serial_huart;

volatile serial_buffer ser_buff;
uint8_t rx_char;
uint8_t tx_buffer[SERIAL_BUFFER_SIZE];

volatile uint8_t tx_complete = 1;

void serial_init(UART_HandleTypeDef *huart)
{
	ser_buff.front = 0;
	ser_buff.back = 0;
	serial_huart = huart;
	HAL_UART_Receive_IT(serial_huart, &rx_char, 1);
}

uint32_t serial_available(void)
{
	if (ser_buff.back > ser_buff.front)
	{
		return ser_buff.back - ser_buff.front;
	}
	else if (ser_buff.back < ser_buff.front)
	{
		return ser_buff.back + SERIAL_BUFFER_SIZE - ser_buff.front;
	}
	else
	{
		return 0;
	}
}

uint8_t serial_read(void)
{
	uint8_t c = (uint8_t)'\0';
	if (serial_available())
	{
		c = ser_buff.buffer[ser_buff.front++];
		if (SERIAL_BUFFER_SIZE == ser_buff.front)
			ser_buff.front = 0;
	}
	return c;
}

void serial_flush()
{
	serial_init(serial_huart);
}

void serial_push_back(char c)
{
	ser_buff.buffer[ser_buff.back++] = c;
	if (ser_buff.back == SERIAL_BUFFER_SIZE)
		ser_buff.back = 0;
}

uint32_t get_back(void)
{
	return ser_buff.back;
}

UART_HandleTypeDef *get_UART_Handle()
{
	return serial_huart;
}

void serial_print(uint8_t *data, uint32_t len)
{
	while (!tx_complete)
		;
	tx_complete = 0;
	HAL_UART_Transmit_IT(serial_huart, data, len);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	serial_push_back(rx_char);
	HAL_UART_Receive_IT(serial_huart, &rx_char, 1);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	tx_complete = 1;
}
