#include "uart_c.h"
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_usart.h>

#ifdef USE_FULL_ASSERT
void
assert_failed(uint8_t* file, uint32_t line)
{
    /* loop but gdb helps :)*/
    while (1)
        ;
}
#endif

// __IO just means voltaile
// and it is volatile because SysTick_Handler
// will modify this value
// and SysTick_Handler is called every tick of the hardware :)
static __IO uint32_t TimingDelay;
void
Delay(uint32_t nTime)
{
    TimingDelay = nTime;
    while (TimingDelay != 0)
        ;
}

void
SysTick_Handler(void)
{
    if (TimingDelay != 0x00)
    {
        TimingDelay--;
    }
}

int
main()
{
    uart_open(USART1, 9600, 0x0);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    // Setting up our cool button
    GPIO_InitTypeDef gpio_button_base;
    GPIO_StructInit(&gpio_button_base);
    gpio_button_base.GPIO_Pin   = GPIO_Pin_0;
    gpio_button_base.GPIO_Speed = GPIO_Speed_2MHz;
    gpio_button_base.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpio_button_base);

    const char string[] = "Big chocolate chip cookie\n\r";

    if (SysTick_Config(SystemCoreClock / 1000))
    {
        while (1)
            ;
    }
    while (1)
    {
        // we can echo what we type but theres a problem now, we can only type
        // in the same line 🤔
        uart_putc(uart_getc(USART1), USART1);
        // Delay(666);
    }
}
