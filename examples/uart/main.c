#include <avr/io.h>

#define UART_BAUD 9600UL
#define UART_UBRR ((F_CPU / (16UL * UART_BAUD)) - 1UL)

static void uart_init(void)
{
    UBRR0H = (uint8_t)(UART_UBRR >> 8);
    UBRR0L = (uint8_t)UART_UBRR;

    UCSR0A = 0;
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);    /* bật thu và phát */
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);  /* 8 data, 1 stop, no parity */
}

static void uart_putc(char c)
{
    while ((UCSR0A & _BV(UDRE0)) == 0U) {
    }
    UDR0 = (uint8_t)c;
}

static void uart_puts(const char *s)
{
    while (*s != '\0') {
        uart_putc(*s++);
    }
}

void setup(void)
{
    uart_init();
    uart_puts("ATmega328P UART register demo\r\n");
    uart_puts("9600 8N1 - go chuoi de echo\r\n");
}

void loop(void)
{
    if ((UCSR0A & _BV(RXC0)) != 0U) {
        char c = (char)UDR0;
        uart_putc(c);                    /* echo */
    }
}
