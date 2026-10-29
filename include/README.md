Các ví dụ dùng trực tiếp thanh ghi AVR trong `avr/io.h`.

File nguồn là C (`.c`), không sử dụng `pinMode`, `digitalWrite`, `Serial`,
`analogRead` hoặc `analogWrite`. Arduino framework của PlatformIO chỉ cung cấp
startup/linker và gọi `setup()`/`loop()`.
