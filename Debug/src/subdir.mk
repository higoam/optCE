################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Generatefiles.cpp \
../src/Run.cpp \
../src/Runalgorithm.cpp \
../src/Set.cpp \
../src/Tcexamples.cpp \
../src/Tflags.cpp \
../src/projeto.cpp 

OBJS += \
./src/Generatefiles.o \
./src/Run.o \
./src/Runalgorithm.o \
./src/Set.o \
./src/Tcexamples.o \
./src/Tflags.o \
./src/projeto.o 

CPP_DEPS += \
./src/Generatefiles.d \
./src/Run.d \
./src/Runalgorithm.d \
./src/Set.d \
./src/Tcexamples.d \
./src/Tflags.d \
./src/projeto.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


