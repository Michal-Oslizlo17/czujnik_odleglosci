#Compiler

#CMSIS_INC=-I/home/kk/eclipse-workspace/CMSIS/Include
#CMSIS_LIBD=-L/home/kk/eclipse-workspace/CMSIS/Lib/GCC
#CMSIS_LIB=-larm_cortexM3l_math # with FPU: larm_cortexM4lf_math , without FPU: larm_cortexM4l_math
PROC=-DARM_MATH_CM3

#TD=/usr/bin
#TD=/usr/local/share/bleeding-edge-toolchain-180127/installNative/bin/
TD=

CC=$(TD)arm-none-eabi-gcc
LD=$(TD)arm-none-eabi-g++

#Include files
INC = -Iinclude

#Compiler flags
CFLAGS = $(INC) -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -g3 -O0 $(PROC) $(CMSIS_INC) 

#Linker flags 
LFLAGS = -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -specs=nosys.specs -T STM32F103C8Tx_FLASH.ld -Wl,--gc-sections -lm  

#Linking
all: configure_GPIO_inputs.o ftoa.o uart.o timery.o main.o startup_stm32f103xb.o
	$(LD) $(LFLAGS)  output/configure_GPIO_inputs.o output/ftoa.o output/uart.o output/timery.o output/main.o output/startup_stm32f103xb.o -o output/program.elf $(CMSIS_LIBD)  $(CMSIS_LIB)

#Compiling main.c
main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o output/main.o

timery.o: src/timery.c
	$(CC) $(CFLAGS) -c src/timery.c -o output/timery.o 

uart.o: src/timery.c
	$(CC) $(CFLAGS) -c src/uart.c -o output/uart.o

ftoa.o: src/ftoa.c
	$(CC) $(CFLAGS) -c src/ftoa.c -o output/ftoa.o

configure_GPIO_inputs.o: src/configure_GPIO_inputs.c
	$(CC) $(CFLAGS) -c src/configure_GPIO_inputs.c -o output/configure_GPIO_inputs.o

#Compiling startup_stm32f103xb.s
startup_stm32f103xb.o: src/startup_stm32f103xb.s
	$(CC) $(CFLAGS) -c src/startup_stm32f103xb.s -o output/startup_stm32f103xb.o

#Cleaning
clean:
	del output\*.* /q

