################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Dho/DhoCore.c \
../src/Dho/DhoMpc.c \
../src/Dho/DhoMpr.c 

OBJS += \
./src/Dho/DhoCore.o \
./src/Dho/DhoMpc.o \
./src/Dho/DhoMpr.o 

C_DEPS += \
./src/Dho/DhoCore.d \
./src/Dho/DhoMpc.d \
./src/Dho/DhoMpr.d 


# Each subdirectory must supply rules for building sources it contributes
src/Dho/%.o: ../src/Dho/%.c src/Dho/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


