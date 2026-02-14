################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Autosar.c \
../Can_bus.c \
../CtApTis.c \
../DhoCore.c \
../Fum.c \
../Lim.c \
../Simu.c \
../TIS_modelIO.c \
../TIS_modelIO_Lim.c \
../Tis.c \
../Vbm.c \
../xml_utils.c 

OBJS += \
./Autosar.o \
./Can_bus.o \
./CtApTis.o \
./DhoCore.o \
./Fum.o \
./Lim.o \
./Simu.o \
./TIS_modelIO.o \
./TIS_modelIO_Lim.o \
./Tis.o \
./Vbm.o \
./xml_utils.o 

C_DEPS += \
./Autosar.d \
./Can_bus.d \
./CtApTis.d \
./DhoCore.d \
./Fum.d \
./Lim.d \
./Simu.d \
./TIS_modelIO.d \
./TIS_modelIO_Lim.d \
./Tis.d \
./Vbm.d \
./xml_utils.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


