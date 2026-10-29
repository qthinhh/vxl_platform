#include <avr/io.h>
#include <util/delay.h>

/* Đọc ADC0/PC0 và điều khiển độ sáng LED D9 bằng OCR1A. */
static void adc_init(void)
{
    ADMUX = _BV(REFS0);                  /* Vref = AVcc, chọn ADC0 */
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
    ADCSRB = 0;                          /* free running không dùng */
    DIDR0 = _BV(ADC0D);                  /* tắt ngõ vào số trên PC0 */
}

static uint16_t adc_read(uint8_t channel)
{
    ADMUX = _BV(REFS0) | (channel & 0x07U);
    ADCSRA |= _BV(ADSC);
    while ((ADCSRA & _BV(ADIF)) == 0U) {
    }
    ADCSRA |= _BV(ADIF);                 /* xóa cờ bằng ghi 1 */
    return ADC;
}

static void pwm1_init(void)
{
    DDRB |= _BV(PB1);                    /* OC1A / D9 */
    TCCR1A = _BV(COM1A1) | _BV(WGM10);   /* Fast PWM 8-bit */
    TCCR1B = _BV(WGM12) | _BV(CS11);     /* prescaler 8 */
    OCR1A = 0;
}

void setup(void)
{
    adc_init();
    pwm1_init();
}

void loop(void)
{
    OCR1A = (uint8_t)(adc_read(0) >> 2); /* 10 bit -> 8 bit */
    _delay_ms(10);
}
