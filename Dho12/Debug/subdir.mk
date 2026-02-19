################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CtApTis.c \
../Dho.c \
../ExternalCalls.c \
../Fum.c \
../Lim.c \
../Rho.c \
../Rte_CtApTis.c \
../Simu.c \
../TIS_modelIO_Fum.c \
../Tis.c \
../Vbm.c \
../xml_utils.c \
../xml_utils_dtc.c \
../xml_utils_nvm.c 

OBJS += \
./CtApTis.o \
./Dho.o \
./ExternalCalls.o \
./Fum.o \
./Lim.o \
./Rho.o \
./Rte_CtApTis.o \
./Simu.o \
./TIS_modelIO_Fum.o \
./Tis.o \
./Vbm.o \
./xml_utils.o \
./xml_utils_dtc.o \
./xml_utils_nvm.o 

C_DEPS += \
./CtApTis.d \
./Dho.d \
./ExternalCalls.d \
./Fum.d \
./Lim.d \
./Rho.d \
./Rte_CtApTis.d \
./Simu.d \
./TIS_modelIO_Fum.d \
./Tis.d \
./Vbm.d \
./xml_utils.d \
./xml_utils_dtc.d \
./xml_utils_nvm.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


