#include <avr/io.h>
#include <util/delay.h>

#define I2C_SCL_HZ 100000UL
#define I2C_SLAVE_ADDRESS 0x50U          /* ví dụ EEPROM I2C 24Cxx */

static void i2c_init(void)
{
    /* SCL/SDA là PC5/PC4. Cần điện trở kéo lên ngoài, thường 4.7 kOhm. */
    PORTC &= (uint8_t)~(_BV(PC4) | _BV(PC5));
    TWSR = 0;                            /* prescaler = 1 */
    TWBR = (uint8_t)((F_CPU / I2C_SCL_HZ - 16UL) / 2UL);
    TWCR = _BV(TWEN);
}

static uint8_t i2c_start(uint8_t address)
{
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
    while ((TWCR & _BV(TWINT)) == 0U) {
    }

    if ((TWSR & 0xF8U) != 0x08U && (TWSR & 0xF8U) != 0x10U) {
        return 0;
    }

    TWDR = address;
    TWCR = _BV(TWINT) | _BV(TWEN);
    while ((TWCR & _BV(TWINT)) == 0U) {
    }
    return ((TWSR & 0xF8U) == 0x18U || (TWSR & 0xF8U) == 0x40U);
}

static uint8_t i2c_write(uint8_t data)
{
    TWDR = data;
    TWCR = _BV(TWINT) | _BV(TWEN);
    while ((TWCR & _BV(TWINT)) == 0U) {
    }
    return ((TWSR & 0xF8U) == 0x28U);
}

static void i2c_stop(void)
{
    TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}

void setup(void)
{
    i2c_init();
    DDRB |= _BV(PB5);
}

void loop(void)
{
    /* Ghi byte 0xA5 vào ô 0 của EEPROM 24Cxx tại địa chỉ 0x50. */
    uint8_t ok = i2c_start((uint8_t)(I2C_SLAVE_ADDRESS << 1));
    if (ok) {
        ok = i2c_write(0x00);
    }
    if (ok) {
        ok = i2c_write(0xA5);
    }
    i2c_stop();

    if (ok) {
        PORTB |= _BV(PB5);
    } else {
        PORTB &= (uint8_t)~_BV(PB5);
    }
    _delay_ms(1000);
}
