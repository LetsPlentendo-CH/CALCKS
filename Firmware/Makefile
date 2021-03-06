OBJCOPY = avr-objcopy
AVRDUDE = avrdude

PORT=/dev/ttyACM0

LDFLAGS = -lm -lpthread

ifeq ($(OS), Windows_NT)
	SHELL=cmd
	PORT=COM3
	LDFLAGS = -lm
endif

avr-files = avr/buttons.o avr/display.o avr/eep.o
common-files = common/*.h
common-obj = common/gui.o common/term.o common/mandel.o common/graph.o common/mathinput.o common/solver.o
console-files = console/buttons.o console/display.o console/eep.o

default: eeprom upload

%.o: %.c
	$(CC) -c $^ $(CCFLAGS)

pre-avr:
	$(eval CC = avr-gcc)
	$(eval MCU = atmega1284p)
	$(eval CCFLAGS += -std=c99 -mmcu=$(MCU) -O2)
	$(eval LDFLAGS = -Wl,-u,vfprintf -lprintf_flt -lm)

pre-console:
	$(eval CC = gcc)
	$(eval CCFLAGS = -O0 -Dconsole -g -lm -lpthread)

avr: pre-avr main.o $(avr-files) $(common-obj)
	$(CC) main.o $(subst avr/,,$(avr-files)) $(subst common/,,$(common-obj)) $(CCFLAGS) $(LDFLAGS) -o main.elf
	$(OBJCOPY) -O ihex main.elf main.hex
	
console: pre-console main.o $(console-files) $(common-obj)
	$(CC) -o server/calc main.o $(subst console/,,$(console-files)) $(subst common/,,$(common-obj)) $(LDFLAGS)
	cd server && node server.js

eepromprog.hex: pre-avr eepromprog.o $(avr-files)
	$(CC) eepromprog.o $(CCFLAGS) $(subst avr/,,$(avr-files)) -o eepromprog.elf
	$(OBJCOPY) -O ihex eepromprog.elf eepromprog.hex

server/eepromdata.bin: eepromgen/*.png
	node eepromgen/makeEEPROMBin.js eepromgen/calcks.json server/eepromdata.bin

eeprom: server/eepromdata.bin
	$(AVRDUDE) -v -p atmega1284 -c avrisp -P $(PORT) -b 57600 -U eeprom:w:"server/eepromdata.bin":r -B8

upload: avr
	$(AVRDUDE) -v -p atmega1284 -c avrisp -P $(PORT) -b 57600 -U flash:w:"main.hex":i -B8

test: pre-console test_term/test_term.o common/term.o
	$(CC) -g -o test_term/test_term term.o test_term.o $(LDFLAGS)

clean:
	rm *.o
	rm *.elf
	rm *.hex
