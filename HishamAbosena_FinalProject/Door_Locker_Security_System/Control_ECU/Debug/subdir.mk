################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Control_ECU_Functions.c \
../MC2_main.c \
../buzzer.c \
../dcmotor.c \
../external_eeprom.c \
../gpio.c \
../mytwi.c \
../myuart.c \
../pwm_timer0.c \
../timer1.c 

OBJS += \
./Control_ECU_Functions.o \
./MC2_main.o \
./buzzer.o \
./dcmotor.o \
./external_eeprom.o \
./gpio.o \
./mytwi.o \
./myuart.o \
./pwm_timer0.o \
./timer1.o 

C_DEPS += \
./Control_ECU_Functions.d \
./MC2_main.d \
./buzzer.d \
./dcmotor.d \
./external_eeprom.d \
./gpio.d \
./mytwi.d \
./myuart.d \
./pwm_timer0.d \
./timer1.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


