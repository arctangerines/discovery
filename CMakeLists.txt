cmake_minimum_required(VERSION 3.27)
project(discovery C CXX ASM)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)

set(CHIP "stm32f100")
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/stm32f100.ld)

set(DEVICE stlib/CMSIS/CM3/DeviceSupport/ST/STM32F10x)
set(CORE stlib/CMSIS/CM3/CoreSupport)
set(PERIPH stlib/STM32F10x_StdPeriph_Driver)

#processor type def
add_definitions(-DSTM32F10X_MD_VL)

include_directories(${DEVICE})
include_directories(${CORE})
include_directories(${PERIPH}/inc)
include_directories(${CMAKE_SOURCE_DIR}/inc/) #this is for the file stm32f10x_conf.h
                          #this one comes from the template provided by ST

# we have to do this manually as opposed as whenever we need it 
# better for clarity, more laborious upfront :)
set(DISC_FILES
        src/uart/main.c
        src/uart/uart.c
        lib/startup_stm32f10x.c #auto generated but available in the template by prof brown
        stlib/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
        stlib/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
        stlib/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
        stlib/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c
)
include_directories(${CMAKE_SOURCE_DIR}/src/uart/)

set(CMAKE_C_FLAGS "-O1 -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-m3 -mthumb")
add_definitions(-DUSE_STDPERIPH_DRIVER)
add_definitions(-DUSE_FULL_ASSERT)

set(CMAKE_ASM_FLAGS "-g")

set(CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mthumb -mcpu=cortex-m3 -specs=nano.specs -specs=nosys.specs")

add_executable(discovery.elf ${DISC_FILES})


