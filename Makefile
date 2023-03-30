# simple AVR Makefile
#
# written by michael cousins (http://github.com/mcous)
# released to the public domain

# Makefile
#
# targets:
#   all:    compiles the source code
#   test:   tests the isp connection to the mcu
#   flash:  writes compiled hex file to the mcu's flash memory
#   fuse:   writes the fuse bytes to the MCU
#   disasm: disassembles the code for debugging
#   clean:  removes all .hex, .elf, and .o files in the source code and library directories

SRC_DIR = ./src
BUILD_DIR = ./build
AVR_GCC_DIR = c:/opt/avr8-gnu-toolchain-win32_x86_64/bin
AVRDUDE_DIR = c:/opt/avrdude-msvc-x64

MODULES = $(SRC_DIR)/mod_esc


# parameters (change this stuff accordingly)
# project name
PRJ = main
# avr mcu
MCU = atmega328p
# mcu clock frequency
CLK = 16000000
# avr programmer (and port if necessary)
# e.g. PRG = usbtiny -or- PRG = arduino -P /dev/tty.usbmodem411
PRG = usbtiny
# fuse values for avr: low, high, and extended
# these values are from an Arduino Uno (ATMega328P)
# see http://www.engbedded.com/fusecalc/ for other MCUs and options
LFU = 0xFF
HFU = 0xDE
EFU = 0x05
# program source files (not including external libraries)
#MODULES_C = $(foreach dir, $(MODULES), $(wildcard $(dir)/*.c)
MODULES_C = $(wildcard $(SRC_DIR)/mod_*/*.c)
SRC = $(SRC_DIR)/$(PRJ).c $(MODULES_C)
# where to look for external libraries (consisting of .c/.cpp files and .h files)
# e.g. EXT = ../../EyeToSee ../../YouSART
EXT =


#################################################################################################
# \/ stuff nobody needs to worry about until such time that worrying about it is appropriate \/ #
#################################################################################################

# include path
INCLUDE := $(foreach dir, $(EXT), -I$(dir))
# c flags
CFLAGS    = -Wall -Os -DF_CPU=$(CLK) -mmcu=$(MCU) $(INCLUDE)
# any aditional flags for c++
CPPFLAGS =

# executables
AVRDUDE = $(AVR_GCC_PATH)/avrdude.exe -c $(PRG) -p $(MCU)
OBJCOPY = $(AVR_GCC_DIR)/avr-objcopy.exe
OBJDUMP = $(AVR_GCC_DIR)/avr-objdump.exe
SIZE    = $(AVR_GCC_DIR)/avr-size.exe --format=avr --mcu=$(MCU)
CC      = $(AVR_GCC_DIR)/avr-gcc.exe

# generate list of objects
CFILES    = $(filter %.c, $(SRC))
EXTC     := $(foreach dir, $(EXT), $(wildcard $(dir)/*.c))
CPPFILES  = $(filter %.cpp, $(SRC))
EXTCPP   := $(foreach dir, $(EXT), $(wildcard $(dir)/*.cpp))
OBJ      := $(CFILES:.c=.o) $(EXTC:.c=.o) $(CPPFILES:.cpp=.o) $(EXTCPP:.cpp=.o)
OBJ      := $(OBJ:%=$(BUILD_DIR)\\%)

# user targets
# compile all files
all: $(PRJ).hex

# test programmer connectivity
test:
	$(AVRDUDE) -v

# flash program to mcu
flash: all
	$(AVRDUDE) -U flash:w:$(PRJ).hex:i

# write fuses to mcu
fuse:
	$(AVRDUDE) -U lfuse:w:$(LFU):m -U hfuse:w:$(HFU):m -U efuse:w:$(EFU):m

# generate disassembly files for debugging
disasm: $(PRJ).elf
	$(OBJDUMP) -d $(PRJ).elf

# remove compiled files
clean:
	rmdir /s /o $(BUILD_DIR)
#	rm -f *.hex *.elf *.o
#	$(foreach dir, $(EXT), rm -f $(dir)/*.o;)

# other targets
# objects from c files
#.c.o:
#	@echo Compiling $<
#	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)
#
## objects from c++ files
#.cpp.o:
#	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

$(OBJ): %.o:$(BUILD_DIR)\\%.c
	@echo building $<
	$(CC) $(CFLAGS) -c $< -o $@

# elf file
$(PRJ).elf: $(OBJ)
	$(CC) $(CFLAGS) -o $(PRJ).elf $(OBJ)

# hex file
$(PRJ).hex: $(PRJ).elf
	rm -f $(PRJ).hex
	$(OBJCOPY) -j .text -j .data -O ihex $(PRJ).elf $(PRJ).hex
	$(SIZE) $(PRJ).elf
	
hhh:
	@echo $(MODULES_C)
	@echo $(BUILD_OBJ)
