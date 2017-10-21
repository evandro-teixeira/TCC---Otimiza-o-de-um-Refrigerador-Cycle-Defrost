################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Controle_LCD.c" \
"../Sources/LCD.c" \
"../Sources/MCUinit.c" \
"../Sources/Timer.c" \
"../Sources/aplicacao.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/Controle_LCD.c \
../Sources/LCD.c \
../Sources/MCUinit.c \
../Sources/Timer.c \
../Sources/aplicacao.c \
../Sources/main.c \

OBJS += \
./Sources/Controle_LCD_c.obj \
./Sources/LCD_c.obj \
./Sources/MCUinit_c.obj \
./Sources/Timer_c.obj \
./Sources/aplicacao_c.obj \
./Sources/main_c.obj \

OBJS_QUOTED += \
"./Sources/Controle_LCD_c.obj" \
"./Sources/LCD_c.obj" \
"./Sources/MCUinit_c.obj" \
"./Sources/Timer_c.obj" \
"./Sources/aplicacao_c.obj" \
"./Sources/main_c.obj" \

C_DEPS += \
./Sources/Controle_LCD_c.d \
./Sources/LCD_c.d \
./Sources/MCUinit_c.d \
./Sources/Timer_c.d \
./Sources/aplicacao_c.d \
./Sources/main_c.d \

OBJS_OS_FORMAT += \
./Sources/Controle_LCD_c.obj \
./Sources/LCD_c.obj \
./Sources/MCUinit_c.obj \
./Sources/Timer_c.obj \
./Sources/aplicacao_c.obj \
./Sources/main_c.obj \

C_DEPS_QUOTED += \
"./Sources/Controle_LCD_c.d" \
"./Sources/LCD_c.d" \
"./Sources/MCUinit_c.d" \
"./Sources/Timer_c.d" \
"./Sources/aplicacao_c.d" \
"./Sources/main_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Controle_LCD_c.obj: ../Sources/Controle_LCD.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/Controle_LCD.args" -o "Sources/Controle_LCD_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/LCD_c.obj: ../Sources/LCD.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/LCD.args" -o "Sources/LCD_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/MCUinit_c.obj: ../Sources/MCUinit.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/MCUinit.args" -o "Sources/MCUinit_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/Timer_c.obj: ../Sources/Timer.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/Timer.args" -o "Sources/Timer_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/aplicacao_c.obj: ../Sources/aplicacao.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/aplicacao.args" -o "Sources/aplicacao_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


