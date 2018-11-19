################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Execution.cpp \
../src/Setup.cpp \
../src/Tflags.cpp \
../src/optCE.cpp 

OBJS += \
./src/Execution.o \
./src/Setup.o \
./src/Tflags.o \
./src/optCE.o 

CPP_DEPS += \
./src/Execution.d \
./src/Setup.d \
./src/Tflags.d \
./src/optCE.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


