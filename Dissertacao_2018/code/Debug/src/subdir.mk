################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Adjust.cpp \
../src/Execution.cpp \
../src/Generatefiles.cpp \
../src/Setup.cpp \
../src/Tcexamples.cpp \
../src/Tflags.cpp \
../src/Tinput.cpp \
../src/optCE.cpp 

OBJS += \
./src/Adjust.o \
./src/Execution.o \
./src/Generatefiles.o \
./src/Setup.o \
./src/Tcexamples.o \
./src/Tflags.o \
./src/Tinput.o \
./src/optCE.o 

CPP_DEPS += \
./src/Adjust.d \
./src/Execution.d \
./src/Generatefiles.d \
./src/Setup.d \
./src/Tcexamples.d \
./src/Tflags.d \
./src/Tinput.d \
./src/optCE.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


