MCU=atmega328p
FUSE_L=0x62
FUSE_H=0xD9
FUSE_E=0xFF
FUSE_LOCK=0xFF
F_CPU=1000000
CC=avr-gcc
LD=avr-ld
OBJCOPY=avr-objcopy
SIZE=avr-size
AVRDUDE=avrdude
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=main

SRCS = main.c 
DUDECFG= -p ${MCU} -C avrdude_gpio.conf -c pi_3 

test:
	$(AVRDUDE) $(DUDECFG) -F -v

build:
	${CC} ${CFLAGS} -o ${TARGET}.o ${SRCS} 
	${LD} -o ${TARGET}.elf ${TARGET}.o
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.o ${TARGET}.hex
	${SIZE} -C --mcu=${MCU} ${TARGET}.elf

flash:
	$(AVRDUDE) ${DUDECFG} -v -e -U flash:w:${TARGET}.hex:i 

fuse:
	$(AVRDUDE) ${DUDECFG} -v -e -U efuse:w:${FUSE_E}:m -U hfuse:w:${FUSE_H}:m -U lfuse:w:${FUSE_L}:m 

sfuse:
	$(AVRDUDE) ${DUDECFG} -vvvv  -U lock:w:0xFF:m -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -i4000 -F
clean:
	rm -f *.c~ *.h~ *.o *.elf *.hex
