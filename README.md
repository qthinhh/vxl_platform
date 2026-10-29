# ATmega328P register-level với PlatformIO

Bộ ví dụ này dành cho Arduino Uno R3 (ATmega328P, mặc định 16 MHz). Mã ứng
dụng là C thuần ở mức thanh ghi AVR; không gọi các hàm Arduino như `pinMode`,
`digitalWrite`, `Serial`, `analogRead` hay `analogWrite`.

## Ví dụ

| Environment | Nội dung | Chân chính |
| --- | --- | --- |
| `gpio` | GPIO input/output, pull-up, chống dội đơn giản | LED D13/PB5, nút D2/PD2 |
| `uart` | USART 0, 9600 8N1, echo | RX D0/PD0, TX D1/PD1 |
| `spi` | SPI master, mode 0, F_CPU/16 | SS D10, MOSI D11, MISO D12, SCK D13 |
| `i2c` | TWI/I²C master 100 kHz, ghi EEPROM | SDA A4/PC4, SCL A5/PC5 |
| `adc` | ADC0 đọc biến trở, điều khiển PWM D9 | ADC0/A0, OC1A/D9 |
| `ac` | Analog Comparator AIN0/AIN1 | AIN0/D6, AIN1/D7, LED D13 |
| `pwm` | Timer1 Fast PWM 8-bit | OC1A/D9 |
| `timer` | Timer1 CTC và ngắt mỗi 1 giây | LED D13 |

ATmega328P không có ngoại vi tên `APC`; environment tương ứng là `adc`.
Nếu muốn học Analog Comparator, dùng thêm environment `ac`.

## Biên dịch và nạp

```bash
pio run -e gpio
pio run -e uart -t upload
pio device monitor -b 115200
```

Đổi `gpio` thành `uart`, `spi`, `i2c`, `adc`, `ac`, `pwm` hoặc `timer` để
chọn ví dụ khác. Chỉ chạy monitor 115200 cho ví dụ UART.

Lưu ý phần cứng:

- I²C cần điện trở kéo lên SDA/SCL, thường 4.7 kΩ lên 5 V.
- Ví dụ I²C giả định EEPROM 24Cxx ở địa chỉ 7-bit `0x50`; có thể đổi
  `I2C_SLAVE_ADDRESS` trong `examples/i2c/main.c`.
- SPI cần một slave ngoài để nhận byte; D13 đồng thời là SCK và LED tích hợp.
- ADC0 cần tín hiệu trong khoảng 0–Vref. Không đưa điện áp vượt Vcc vào chân.
