################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Alarm.c \
../src/CtApAlm.c \
../src/CtApAlmFifoMgr.c \
../src/CtApAlmLibStackMgr.c \
../src/EemStates.c \
../src/Simu.c \
../src/Vbm.c 

OBJS += \
./src/Alarm.o \
./src/CtApAlm.o \
./src/CtApAlmFifoMgr.o \
./src/CtApAlmLibStackMgr.o \
./src/EemStates.o \
./src/Simu.o \
./src/Vbm.o 

C_DEPS += \
./src/Alarm.d \
./src/CtApAlm.d \
./src/CtApAlmFifoMgr.d \
./src/CtApAlmLibStackMgr.d \
./src/EemStates.d \
./src/Simu.d \
./src/Vbm.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


