BIN = IR-Transmitter

F_CPU = 16000000UL
MCU = atmega328p
BAUDRATE = 115200
PROGRAMMER = arduino
PORT = /dev/ttyS6

CC = avr-gcc
LD=avr-ld
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
AVRSIZE=avr-size

SOURCES = \
		  main.c \
		  led.c \
		  serial.c \
		  timer.c \
		  nec.c

CFLAGS = -g -Wall -pedantic -O2 -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c
LDFLAGS = -mmcu=$(MCU)

OBJS = $(SOURCES:.c=.o)
OUT=${BIN}.elf ${BIN}.hex ${BIN}.lss

flash: all
	avrdude -F -V -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUDRATE) -U flash:w:$(BIN).hex -v

all: $(OUT)

$(OBJS): makefile

%.o:%.c
	$(COMPILE.c) -MD -o $@ $<
	@cp $*.d $*.P; \
		sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
		rm -f $*.d

%.lss: %.elf
	$(OBJDUMP) -h -S -s $< > $@

%.elf: $(OBJS) # L?nka
	$(CC) -Wl,-Map=$(@:.elf=.map) $(LDFLAGS) -o $@ $^
	$(AVRSIZE) $@

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .fuse -R .lock -R .user_signatures -R .comment $< $@

clean:
	@echo " Cleaning...";
	rm -f $(OUT) $(OBJS) *.map *.P *.out 
