#ifndef _UART_C_H
#define _UART_C_H

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_usart.h>

int
uart_open(USART_TypeDef* USARTx, uint32_t baud, uint32_t flags);

int
uart_putc(int c, USART_TypeDef* USARTx);

int
uart_putstr(const char* str, USART_TypeDef* USARTx);

int
uart_getc(USART_TypeDef* USARTx);

#endif