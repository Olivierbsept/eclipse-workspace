################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Dho/FctOnOff/FctOnOff.c 

OBJS += \
./src/Dho/FctOnOff/FctOnOff.o 

C_DEPS += \
./src/Dho/FctOnOff/FctOnOff.d 


# Each subdirectory must supply rules for building sources it contributes
src/Dho/FctOnOff/%.o: ../src/Dho/FctOnOff/%.c src/Dho/FctOnOff/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


