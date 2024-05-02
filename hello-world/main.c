#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <stdio.h>
#include <util/delay.h>

#define UNUSED(x) (void)(x)

#define USART_BAUDRATE (57600)
#define USART_UBRR1H (((F_CPU / (16UL * USART_BAUDRATE)) - 1) >> 8)
#define USART_UBRR1L ((F_CPU / (16UL * USART_BAUDRATE)) - 1)

static FILE usart_io;

static int usart_putc(const char c, FILE *stream) {
  UNUSED(stream);
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
  return 0;
}

static int usart_getc(FILE *stream) {
  UNUSED(stream);
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}

static void init_hardware(void) {
  cli();

  MCUSR &= ~(1 << WDRF);

  wdt_disable();

  fdev_setup_stream(&usart_io, usart_putc, usart_getc, _FDEV_SETUP_RW);

  stdin = &usart_io;
  stdout = &usart_io;

  UBRR0H = USART_UBRR1H;
  UBRR0L = USART_UBRR1L;

  UCSR0B = (1 << TXEN0) | (1 << RXEN0);

  UCSR0C = (1 << USBS0) | (3 << UCSZ00);

  sei();
}

int main(void) {

  init_hardware();

  while (1) {
    printf("Hello, World!\r\n");
    _delay_ms(1000);
  }
}
