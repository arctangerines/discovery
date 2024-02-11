#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

void
Delay(uint32_t nTime);

int
main(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    // Enable peripheral clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    // Configure Pins
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_Button_InitStruct;
    GPIO_StructInit(&GPIO_Button_InitStruct);
    GPIO_Button_InitStruct.GPIO_Pin   = GPIO_Pin_0;
    GPIO_Button_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Button_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_Button_InitStruct);

    /* NOTE: This could be edited to make it so its updated every x amount of
       time as opposed to as fast it possibly can lol */
    while (1)
    {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
        {
            GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_SET);
        }
        else
        {
            GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_RESET);
        }
    }
}

#ifdef USE_FULL_ASSERT
void
assert_failed(uint8_t* file, uint32_t line)
{
    /* Infinite loop*/
    /* GDB can help us find out why this happened*/
    while (1)
        ;
}
#endif