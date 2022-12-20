#ifndef SERIAL_H
#define SERIAL_H

#include "main.h"

#define SERIAL_BUFFER_SIZE 1024

typedef struct serial_buffer_struct {
	uint8_t buffer[SERIAL_BUFFER_SIZE];
	volatile uint32_t front;
	volatile uint32_t back;
} serial_buffer;

void serial_init(UART_HandleTypeDef *huart);
uint32_t serial_available(void);
uint8_t serial_read(void);
void serial_flush(void);
void serial_push_back(char c);
uint32_t get_back(void);

UART_HandleTypeDef *get_UART_Handle();

void serial_print(uint8_t *data, uint32_t len);

#endif /* SERIAL_H */
