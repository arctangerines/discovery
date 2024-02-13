#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_usart.h>

#include "uart_c.h"

/**
 * @brief Initialize as UART the specified UART
 * @param USARTX The specified USART device to initialize (1-5)
 * @param baud Baud rate, has to be multiple of 9600
 * @retval 0 if theres no errors, 1 if it failed
 * @note This can be more robust because we never use any of these params except
 * for baud. Like, the example implementation used USARTx but... it only does 1
 * comparison, and USARTx is the USART number and we can make this moooore
 * robust. So im not even including this comparison.
 */
int
uart_open(USART_TypeDef* USARTx, uint32_t baud, uint32_t flags)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO |
                               RCC_APB2Periph_GPIOA,
                           ENABLE);
    // This is the var we will use for the USART GPIO pins we are setting up
    GPIO_InitTypeDef usart_pin_base;
    GPIO_StructInit(&usart_pin_base);

    // config TX
    usart_pin_base.GPIO_Pin   = GPIO_Pin_9;
    usart_pin_base.GPIO_Speed = GPIO_Speed_50MHz;
    usart_pin_base.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &usart_pin_base);

    // This is RX so its In
    usart_pin_base.GPIO_Pin  = GPIO_Pin_10;
    usart_pin_base.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &usart_pin_base);

    // Configure USART (in this case as UART)
    USART_InitTypeDef usart_base;

    USART_StructInit(&usart_base);

    usart_base.USART_BaudRate = baud;
    usart_base.USART_Mode     = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USARTx, &usart_base);
    USART_Cmd(USARTx, ENABLE);

    return 0;
}

int
uart_putc(int c, USART_TypeDef* USARTx)
{
    // we can make it so this is not hardcoded  with a struct :)
    // btw this code is shorthand for saying if there is nothing dont loop
    // but if there is something just loop until its empty (1 == 0)
    // USART_FLAG_TXE means transmitter empty
    // we just checking if there things lolz
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
        ;
    // DR stands for data register
    // contains the data :)
    USARTx->DR = (c & 0xff);
    return 0;
}
int
uart_putstr(const char* str, USART_TypeDef* USARTx)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        uart_putc(str[i], USARTx);
    }
}

int
uart_getc(USART_TypeDef* USARTx)
{
    // we just saying if its empty loop until theres something
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        ;
    // a lot of assumptions here, first that there is a int/char in there
    // second that idkf ykwim
    return USARTx->DR & 0xff;
}