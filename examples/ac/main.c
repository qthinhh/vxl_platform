#include <avr/io.h>
#include <util/delay.h>

/* Analog Comparator: AIN0/PD6 so với AIN1/PD7, ngõ ra AC lưu trong ACO. */
static void comparator_init(void)
{
    DDRD &= (uint8_t)~(_BV(PD6) | _BV(PD7));
    PORTD &= (uint8_t)~(_BV(PD6) | _BV(PD7));
    DIDR1 = _BV(AIN0D) | _BV(AIN1D);     /* tắt buffer số */
    ADCSRB &= (uint8_t)~_BV(ACME);        /* AIN1 làm ngõ vào âm */
    ACSR = 0;                             /* không interrupt, không bandgap */
}

void setup(void)
{
    comparator_init();
    DDRB |= _BV(PB5);                     /* LED D13 */
}

void loop(void)
{
    /* ACO=1 khi AIN0 > AIN1. */
    if ((ACSR & _BV(ACO)) != 0U) {
        PORTB |= _BV(PB5);
    } else {
        PORTB &= (uint8_t)~_BV(PB5);
    }
    _delay_ms(1);
}
