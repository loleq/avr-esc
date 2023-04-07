PRJ=avr-esc
PRJ_HEX=$(PRJ).hex
PRJ_ELF=$(PRJ).elf
PRJ_LST=$(PRJ).lst

#Device
MCU=atmega328p
#Port
PORT=COM4


#Compiler
CC=avr-gcc
OBJ_DUMP = avr-objdump
SYMBOLS=-D F_CPU=16000000UL
#CFLAGS=-O1 -mmcu=$(MCU) $(INCLUDE_DIRS:%=-I "%") $(SYMBOLS) -Wall -Wextra -Wundef -pedantic \
#	-funsigned-char -funsigned-bitfields -ffunction-sections -fdata-sections \
#	-fpack-struct -fshort-enums
	
CFLAGS=-O1 -mmcu=$(MCU) $(INCLUDE_DIRS:%=-I "%") $(SYMBOLS) -Wall -Wextra -Wundef \
	-funsigned-char -funsigned-bitfields -ffunction-sections -fdata-sections \
	-fpack-struct -fshort-enums
	
LFLAGS=-mmcu=$(MCU)

#Hex generator
HC=avr-objcopy
HFLAGS=-j .text -j .data -O ihex

#Print size
SIZE=avr-size -C --mcu=$(MCU)

#Programmer
PROG=avrdude -P"$(PORT)" -p$(MCU) -carduino -b115200

#File locations
INC=../inc
SRC=./src
BUILD=./build

#Files
#SOURCES=$(wildcard $(SRC)/**/*.c) $(wildcard $(SRC)/*.c)
SOURCES=$(shell find $(SRC) -name *.c)
SRCOBJS=$(patsubst $(SRC)/%,$(BUILD)/%,$(SOURCES:.c=.o))

#INCLUDES=$(wildcard $(SRC)/*.h) $(wildcard $(SRC)/**/*.h)
INCLUDES=$(shell find $(SRC) -name *.h)
INCLUDE_DIRS = $(sort $(dir $(INCLUDES)))

#Make all tests AND all sources for demonstration and compile testing
all: $(PRJ_HEX) $(SRCOBJS)

$(PRJ_HEX): $(PRJ).elf
	$(HC) $(HFLAGS) $< $@

$(PRJ_ELF): $(SRCOBJS)
	$(CC) $(LFLAGS) -o $@ $^
	$(SIZE) $@


$(SRCOBJS): $(BUILD)/%.o: $(SRC)/%.c $(INCLUDES)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

#Flashing
prog: $(PRJ_HEX)
	$(PROG) -Uflash:w:"$(PRJ_HEX)":i

memmap: $(PRJ_ELF)
	$(OBJ_DUMP) -x $(PRJ_ELF) > $(PRJ_LST)

#Cleaning
.PHONY: clean prog all memmap
clean:
	rm -rf $(BUILD)
	rm -f $(PRJ_HEX) $(PRJ_ELF) $(PRJ_LST)
#	find . -type f \( -name *.o -o -name *.hex -o -name *.elf \) -delete

print_vars:
	@echo $(INCLUDES)
	@echo $(INCLUDE_DIRS)