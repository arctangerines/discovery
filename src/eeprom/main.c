#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_usart.h>

int
main()
{
    GPIO_InitTypeDef spi_gpio_base;

    GPIO_StructInit(&spi_gpio_base);

    // Init SCK
    spi_gpio_base.GPIO_Pin = GPIO_Pin_5;
    spi_gpio_base.GPIO_Mode = GPIO_Mode_AF_PP;
    spi_gpio_base.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &spi_gpio_base);

    // Init MISO
    spi_gpio_base.GPIO_Pin = GPIO_Pin_6;
    spi_gpio_base.GPIO_Mode = GPIO_Mode_IPU;
    spi_gpio_base.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &spi_gpio_base);

    //Init MOSI
    spi_gpio_base.GPIO_Pin = GPIO_Pin_7;
    spi_gpio_base.GPIO_Mode = GPIO_Mode_AF_PP;
    spi_gpio_base.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &spi_gpio_base);
}