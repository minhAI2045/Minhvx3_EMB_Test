################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FTM.c \
../src/FlexCAN.c \
../src/GPIO.c \
../src/LPIT.c \
../src/LUART.c \
../src/Middleware.c \
../src/NVIC.c \
../src/PORT.c \
../src/clocks_and_modes.c \
../src/main.c 

OBJS += \
./src/FTM.o \
./src/FlexCAN.o \
./src/GPIO.o \
./src/LPIT.o \
./src/LUART.o \
./src/Middleware.o \
./src/NVIC.o \
./src/PORT.o \
./src/clocks_and_modes.o \
./src/main.o 

C_DEPS += \
./src/FTM.d \
./src/FlexCAN.d \
./src/GPIO.d \
./src/LPIT.d \
./src/LUART.d \
./src/Middleware.d \
./src/NVIC.d \
./src/PORT.d \
./src/clocks_and_modes.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/FTM.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


