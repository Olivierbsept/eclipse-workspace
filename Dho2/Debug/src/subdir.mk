################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/CAN.c \
../src/Common.c \
../src/Dho2.c \
../src/Fum.c \
../src/Ram.c \
../src/Vbm.c 

OBJS += \
./src/CAN.o \
./src/Common.o \
./src/Dho2.o \
./src/Fum.o \
./src/Ram.o \
./src/Vbm.o 

C_DEPS += \
./src/CAN.d \
./src/Common.d \
./src/Dho2.d \
./src/Fum.d \
./src/Ram.d \
./src/Vbm.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


