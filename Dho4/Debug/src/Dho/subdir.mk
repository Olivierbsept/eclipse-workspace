################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Dho/DhoCore.c \
../src/Dho/DhoMic.c \
../src/Dho/DhoMir.c \
../src/Dho/DhoMpc.c \
../src/Dho/DhoMpr.c 

OBJS += \
./src/Dho/DhoCore.o \
./src/Dho/DhoMic.o \
./src/Dho/DhoMir.o \
./src/Dho/DhoMpc.o \
./src/Dho/DhoMpr.o 

C_DEPS += \
./src/Dho/DhoCore.d \
./src/Dho/DhoMic.d \
./src/Dho/DhoMir.d \
./src/Dho/DhoMpc.d \
./src/Dho/DhoMpr.d 


# Each subdirectory must supply rules for building sources it contributes
src/Dho/%.o: ../src/Dho/%.c src/Dho/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


