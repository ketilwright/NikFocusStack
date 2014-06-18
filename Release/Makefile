################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Scripts


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../Adafruit_MCP23017.cpp \
../Adafruit_RGBLCDShield.cpp \
../Button.cpp \
../Main.cpp \
../MainMenu.cpp \
../MessageHandler.cpp \
../MessagePump.cpp \
../NikType003.cpp \
../NikType003State.cpp \
../ReadAdaFruitLcdButtonState.cpp \
../RunFocusStackHandler.cpp \
../SetupHandler.cpp \
../twi.c \
../Wire.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
Adafruit_MCP23017.o \
Adafruit_RGBLCDShield.o \
Button.o \
Main.o \
MainMenu.o \
MessageHandler.o \
MessagePump.o \
NikType003.o \
NikType003State.o \
ReadAdaFruitLcdButtonState.o \
RunFocusStackHandler.o \
SetupHandler.o \
twi.o \
Wire.o

OBJS_AS_ARGS +=  \
Adafruit_MCP23017.o \
Adafruit_RGBLCDShield.o \
Button.o \
Main.o \
MainMenu.o \
MessageHandler.o \
MessagePump.o \
NikType003.o \
NikType003State.o \
ReadAdaFruitLcdButtonState.o \
RunFocusStackHandler.o \
SetupHandler.o \
twi.o \
Wire.o

C_DEPS +=  \
Adafruit_MCP23017.d \
Adafruit_RGBLCDShield.d \
Button.d \
Main.d \
MainMenu.d \
MessageHandler.d \
MessagePump.d \
NikType003.d \
NikType003State.d \
ReadAdaFruitLcdButtonState.d \
RunFocusStackHandler.d \
SetupHandler.d \
twi.d \
Wire.d

C_DEPS_AS_ARGS +=  \
Adafruit_MCP23017.d \
Adafruit_RGBLCDShield.d \
Button.d \
Main.d \
MainMenu.d \
MessageHandler.d \
MessagePump.d \
NikType003.d \
NikType003State.d \
ReadAdaFruitLcdButtonState.d \
RunFocusStackHandler.d \
SetupHandler.d \
twi.d \
Wire.d

OUTPUT_FILE_PATH +=NikFocusStackAdaFruitLcdShield.elf

OUTPUT_FILE_PATH_AS_ARGS +=NikFocusStackAdaFruitLcdShield.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler





























./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DF_CPU=16000000 -DARDUINO=104 -DARDUINO_UNO=1 -DNDEBUG  -I"%ATE_HOME%\Boards\Uno\Headers"  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -Wall -mmcu=atmega328p -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./%.o: .././%.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DF_CPU=16000000 -DARDUINO=104 -DARDUINO_UNO=1 -DNDEBUG  -I"%ATE_HOME%\Boards\Uno\Headers" -I"C:\projects\embedded\arduino\NikFocusStack\libs\USB_Host_Shield_2.0" -I"C:\projects\embedded\arduino\NikFocusStack\libs\PTP_2.0"  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -Wall -mmcu=atmega328p -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR8/GNU Linker : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="NikFocusStackAdaFruitLcdShield.map" -Wl,--start-group -Wl,-lm -Wl,-lArduinoCore -Wl,-lptp2 -Wl,-lusb2Host  -Wl,--end-group -Wl,-L"%ATE_HOME%\Boards\Uno\Libs\16" -Wl,-L"../../libs/USB_Host_Shield_2.0/Release" -Wl,-L"../../libs/PTP_2.0/Release"  -Wl,--gc-sections -mrelax -mmcu=atmega328p  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "NikFocusStackAdaFruitLcdShield.elf" "NikFocusStackAdaFruitLcdShield.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "NikFocusStackAdaFruitLcdShield.elf" "NikFocusStackAdaFruitLcdShield.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "NikFocusStackAdaFruitLcdShield.elf" > "NikFocusStackAdaFruitLcdShield.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "NikFocusStackAdaFruitLcdShield.elf" "NikFocusStackAdaFruitLcdShield.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1056\avr8-gnu-toolchain\bin\avr-size.exe" "NikFocusStackAdaFruitLcdShield.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "NikFocusStackAdaFruitLcdShield.elf" "NikFocusStackAdaFruitLcdShield.a" "NikFocusStackAdaFruitLcdShield.hex" "NikFocusStackAdaFruitLcdShield.lss" "NikFocusStackAdaFruitLcdShield.eep" "NikFocusStackAdaFruitLcdShield.map" "NikFocusStackAdaFruitLcdShield.srec" "NikFocusStackAdaFruitLcdShield.usersignatures"
	