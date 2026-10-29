#include <avr/io.h>
#include <util/delay.h>

/* Timer1 Fast PWM 8-bit trên OC1A/PB1/D9, f_PWM xấp xỉ 7.8 kHz. */
static void pwm_init(void)
{
    DDRB |= _BV(PB1);
    TCCR1A = _BV(COM1A1) | _BV(WGM10);   /* non-inverting, Fast PWM 8-bit */
    TCCR1B = _BV(WGM12) | _BV(CS11);     /* clock / 8 */
    OCR1A = 0;
}

void setup(void)
{
    pwm_init();
}

void loop(void)
{
    uint16_t duty;

    for (duty = 0; duty < 256U; duty++) {
        OCR1A = (uint8_t)duty;
        _delay_ms(4);
    }
    for (duty = 255U; duty > 0U; duty--) {
        OCR1A = (uint8_t)duty;
        _delay_ms(4);
    }
}
