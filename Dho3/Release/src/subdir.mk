################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Dho3.c \
../src/Fum.c \
../src/Ram.c \
../src/Vbm.c \
../src/xml_utils.c 

OBJS += \
./src/Dho3.o \
./src/Fum.o \
./src/Ram.o \
./src/Vbm.o \
./src/xml_utils.o 

C_DEPS += \
./src/Dho3.d \
./src/Fum.d \
./src/Ram.d \
./src/Vbm.d \
./src/xml_utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


