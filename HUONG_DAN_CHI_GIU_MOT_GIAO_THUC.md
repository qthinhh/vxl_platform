# Chỉ sử dụng một giao thức trong PlatformIO

Tài liệu này hướng dẫn rút gọn project PlatformIO cho Arduino Uno R3 để chỉ
còn một giao thức, ví dụ ADC.

## 1. Cấu trúc project tối giản

Sau khi rút gọn, project chỉ cần:

```text
project/
├── platformio.ini
└── src/
    └── main.c
```

Có thể giữ lại `README.md` hoặc các tài liệu Markdown khác. Các thư mục ví dụ
không sử dụng có thể xóa.

## 2. Đưa chương trình giao thức vào `src/main.c`

Ví dụ muốn chỉ sử dụng ADC:

1. Mở file `examples/adc/main.c`.
2. Sao chép toàn bộ nội dung vào `src/main.c`.
3. Sau đó có thể xóa thư mục `examples/` nếu không còn cần các ví dụ khác.

File `src/main.c` sẽ chứa trực tiếp mã ADC dùng thanh ghi ATmega328P:

```c
#include <avr/io.h>
#include <util/delay.h>

static void adc_init(void)
{
    ADMUX = _BV(REFS0);                  /* Vref = AVcc, chọn ADC0 */
    ADCSRA = _BV(ADEN) | _BV(ADPS2) |
             _BV(ADPS1) | _BV(ADPS0);   /* bật ADC, prescaler 128 */
    DIDR0 = _BV(ADC0D);                  /* tắt ngõ vào số của ADC0 */
}

static uint16_t adc_read(void)
{
    ADCSRA |= _BV(ADSC);                 /* bắt đầu chuyển đổi */
    while ((ADCSRA & _BV(ADIF)) == 0U) {
    }
    ADCSRA |= _BV(ADIF);                 /* xóa cờ hoàn tất */
    return ADC;
}

void setup(void)
{
    adc_init();
}

void loop(void)
{
    uint16_t value = adc_read();
    (void)value;
    _delay_ms(10);
}
```

Trong ứng dụng thực tế, giá trị `value` có thể được gửi qua UART, hiển thị
lên LCD hoặc dùng để điều khiển PWM.

## 3. Cấu hình `platformio.ini`

Khi chỉ còn một chương trình, không cần macro `DEMO_ADC` hoặc các environment
khác. Nội dung tối giản của `platformio.ini` là:

```ini
[platformio]
default_envs = uno

[env:uno]
platform = atmelavr
board = uno
framework = arduino
monitor_speed = 115200
```

Mã ứng dụng vẫn là file C và dùng trực tiếp thanh ghi AVR. Arduino framework
chỉ cung cấp phần khởi động và gọi hai hàm `setup()` và `loop()`.

## 4. Biên dịch và nạp chương trình

Mở terminal tại thư mục project rồi chạy:

```bash
pio run
```

Nếu build thành công, nạp chương trình vào Arduino Uno bằng:

```bash
pio run -t upload
```

## 5. Giữ lại thư mục `examples`

Nếu muốn giữ chương trình ADC ở `examples/adc/main.c` thay vì sao chép vào
`src/main.c`, có thể dùng `src/main.c` như sau:

```c
#include "../examples/adc/main.c"
```

Khi đó cấu trúc project là:

```text
project/
├── platformio.ini
├── src/
│   └── main.c
└── examples/
    └── adc/
        └── main.c
```

## 6. Đổi sang giao thức khác

Để chỉ sử dụng UART, SPI, I²C, PWM hoặc Timer:

1. Sao chép nội dung file tương ứng vào `src/main.c`.
2. Xóa hoặc giữ lại các ví dụ khác tùy nhu cầu.
3. Giữ nguyên `platformio.ini`.
4. Chạy lại:

```bash
pio run -t upload
```

Các file nguồn tương ứng trong project:

```text
examples/gpio/main.c
examples/uart/main.c
examples/spi/main.c
examples/i2c/main.c
examples/adc/main.c
examples/pwm/main.c
examples/timer/main.c
```

## 7. Lưu ý phần cứng

- ADC0 tương ứng chân A0/PC0 trên Arduino Uno.
- Điện áp vào ADC phải nằm trong khoảng 0 V đến Vref, thông thường là 5 V.
- UART dùng RX/D0 và TX/D1.
- I²C dùng SDA/A4 và SCL/A5, cần điện trở kéo lên.
- PWM D9 và Timer1 không nên dùng đồng thời trong cùng một chương trình nếu
  cả hai cùng cấu hình Timer1.
