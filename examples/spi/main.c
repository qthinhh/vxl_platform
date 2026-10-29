#include <avr/io.h>
#include <util/delay.h>

/* Uno SPI: SS=PB2/D10, MOSI=PB3/D11, MISO=PB4/D12, SCK=PB5/D13 */
static void spi_init_master(void)
{
    DDRB |= _BV(PB2) | _BV(PB3) | _BV(PB5);
    DDRB &= (uint8_t)~_BV(PB4);

    PORTB |= _BV(PB2);                   /* SS không chọn slave */
    SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0); /* f_SCK = F_CPU/16, mode 0 */
    SPSR = 0;
}

static uint8_t spi_transfer(uint8_t data)
{
    SPDR = data;
    while ((SPSR & _BV(SPIF)) == 0U) {
    }
    return SPDR;
}

void setup(void)
{
    spi_init_master();
    DDRB |= _BV(PB5);                    /* LED D13 dùng chung chân SCK */
}

void loop(void)
{
    /* Kết nối một SPI slave vào D10-D13 để quan sát byte 0x55.
       Nếu không có slave, phép truyền vẫn hoàn tất và LED sẽ nhấp nháy. */
    PORTB &= (uint8_t)~_BV(PB2);         /* SS low */
    (void)spi_transfer(0x55);
    PORTB |= _BV(PB2);                   /* SS high */

    PINB = _BV(PB5);                     /* đảo LED bằng ghi vào PINB */
    _delay_ms(500);
}
