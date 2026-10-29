/*
 * PlatformIO biên dịch thư mục src/. Mỗi environment chọn một ví dụ bằng
 * macro; các chương trình độc lập vẫn được lưu rõ ràng trong examples/.
 */
#if defined(DEMO_GPIO)
#include "../examples/gpio/main.c"
#elif defined(DEMO_UART)
#include "../examples/uart/main.c"
#elif defined(DEMO_SPI)
#include "../examples/spi/main.c"
#elif defined(DEMO_I2C)
#include "../examples/i2c/main.c"
#elif defined(DEMO_ADC)
#include "../examples/adc/main.c"
#elif defined(DEMO_AC)
#include "../examples/ac/main.c"
#elif defined(DEMO_PWM)
#include "../examples/pwm/main.c"
#elif defined(DEMO_TIMER)
#include "../examples/timer/main.c"
#else
#error "Chon mot environment: gpio, uart, spi, i2c, adc, ac, pwm hoac timer"
#endif
