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

int
putchar(int c)
{
    // we can make it so this is not hardcoded  with a struct :)
    // btw this code is shorthand for saying if there is nothing dont loop
    // but if there is something just loop until its empty (1 == 0)
    // USART_FLAG_TXE means transmitter empty
    // we just checking if there things lolz
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        ;
    // DR stands for data register
    // contains the data :)
    USART1->DR = (c & 0xff);
    return 0;
}
int
putstr(const char* str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        putchar(str[i]);
    }
}

int
getchar(int c)
{
    // we just saying if its empty loop until theres something
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        ;
    // a lot of assumptions here, first that there is a int in there
    // second that idkf ykwim
    return USART1->DR & 0xff;
}

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
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO |
                               RCC_APB2Periph_GPIOA,
                           ENABLE);

    GPIO_InitTypeDef gpio_button_base;
    GPIO_StructInit(&gpio_button_base);
    gpio_button_base.GPIO_Pin   = GPIO_Pin_0;
    gpio_button_base.GPIO_Speed = GPIO_Speed_2MHz;
    gpio_button_base.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpio_button_base);

    // Configure pin
    GPIO_InitTypeDef gpio_base;
    GPIO_StructInit(&gpio_base);

    // config TX
    gpio_base.GPIO_Pin   = GPIO_Pin_9;
    gpio_base.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_base.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &gpio_base);

    // This is RX so its In
    gpio_base.GPIO_Pin  = GPIO_Pin_10;
    gpio_base.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpio_base);

    // Configure USART (in this case UART (?))
    USART_InitTypeDef usart_base;

    USART_StructInit(&usart_base);

    usart_base.USART_BaudRate = 9600;
    usart_base.USART_Mode     = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &usart_base);
    USART_Cmd(USART1, ENABLE);

    const char string[] = "Big chocolate chip cookie\n\r";

    if (SysTick_Config(SystemCoreClock / 1000))
    {
        while (1)
            ;
    }
    while (1)
    {
        static int toggle = 0;
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
        {
            toggle ^= 1;
            putstr("toggle\n");
        }
        if (toggle)
        {
            putstr(string);
        }
        Delay(666);
    }
}
