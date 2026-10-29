#include <avr/io.h>
#include <avr/interrupt.h>

/* Timer1 CTC: 16 MHz / 1024 / (15624+1) = 1 Hz. */
static void timer1_ctc_init(void)
{
    TCCR1A = 0;
    TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10);
    OCR1A = 15624U;
    TIMSK1 = _BV(OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
    PINB = _BV(PB5);                     /* đảo LED không cần đọc-modify-write */
}

void setup(void)
{
    DDRB |= _BV(PB5);                    /* LED D13 */
    timer1_ctc_init();
    sei();
}

void loop(void)
{
    /* CPU rảnh; Timer1 tạo ngắt đều đặn mỗi 1 giây. */
}
