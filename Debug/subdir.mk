################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AiPlayer.cpp \
../Board.cpp \
../Game.cpp \
../GameLogic.cpp \
../HumanPlayer.cpp \
../Player.cpp \
../Point.cpp \
../ReversiLogic.cpp \
../main.cpp 

O_SRCS += \
../AiPlayer.o \
../Board.o \
../Game.o \
../GameLogic.o \
../HumanPlayer.o \
../Player.o \
../Point.o \
../ReversiLogic.o \
../main.o 

OBJS += \
./AiPlayer.o \
./Board.o \
./Game.o \
./GameLogic.o \
./HumanPlayer.o \
./Player.o \
./Point.o \
./ReversiLogic.o \
./main.o 

CPP_DEPS += \
./AiPlayer.d \
./Board.d \
./Game.d \
./GameLogic.d \
./HumanPlayer.d \
./Player.d \
./Point.d \
./ReversiLogic.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


