################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HMI_ECU_Functions.c \
../MC1_main.c \
../gpio.c \
../keypad.c \
../lcd.c \
../myuart.c \
../timer1.c 

OBJS += \
./HMI_ECU_Functions.o \
./MC1_main.o \
./gpio.o \
./keypad.o \
./lcd.o \
./myuart.o \
./timer1.o 

C_DEPS += \
./HMI_ECU_Functions.d \
./MC1_main.d \
./gpio.d \
./keypad.d \
./lcd.d \
./myuart.d \
./timer1.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


