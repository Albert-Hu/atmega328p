CFLAGS = -mmcu=atmega328p -O1 -Wall -DF_CPU=16000000UL
BUILD = build

all:
	mkdir -p $(BUILD)
	avr-gcc $(CFLAGS) -o $(BUILD)/main.elf main.c
	avr-objcopy -O ihex $(BUILD)/main.elf $(BUILD)/main.hex
	avr-size --mcu=atmega328p --format=avr $(BUILD)/main.elf

clean:
	rm -rf $(BUILD)

.PHONY: build clean