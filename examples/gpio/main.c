#include <avr/io.h>
#include <util/delay.h>

/* Arduino Uno: LED tích hợp ở PB5/D13, nút nhấn ở PD2/D2 */
static void gpio_init(void)
{
    DDRB |= _BV(PB5);                    /* PB5 output */
    DDRD &= (uint8_t)~_BV(PD2);          /* PD2 input */
    PORTD |= _BV(PD2);                   /* pull-up nội */
}

void setup(void)
{
    gpio_init();
}

void loop(void)
{
    /* Nút nhấn nối giữa D2 và GND: nhấn = mức 0 */
    if ((PIND & _BV(PD2)) == 0U) {
        PORTB |= _BV(PB5);
    } else {
        PORTB &= (uint8_t)~_BV(PB5);
    }

    _delay_ms(10);                      /* chống dội đơn giản */
}
