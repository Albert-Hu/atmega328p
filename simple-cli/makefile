SRCS = main.c \
			 command.c \
       $(wildcard ../libs/mcucli/src/*.c)
CFLAGS = -mmcu=atmega328p -O1 -Wall -DF_CPU=16000000UL -I. -I../libs/mcucli/include
BUILD = build

all:
	mkdir -p $(BUILD)
	avr-gcc $(CFLAGS) -o $(BUILD)/main.elf $(SRCS)
	avr-objcopy -O ihex $(BUILD)/main.elf $(BUILD)/main.hex
	avr-size --mcu=atmega328p --format=avr $(BUILD)/main.elf

clean:
	rm -rf $(BUILD)

.PHONY: build clean