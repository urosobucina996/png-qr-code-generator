# PNG QR Code Generator

This is a simple C program that reads text from standard input and generates a QR code as a PNG image.

It uses the **qrcodegen** library to create the QR code and **TinyPngOut** to write the PNG file.

## Build
```bash
gcc -Wall -Wextra -O2 -Iinclude src/png_maker.c src/TinyPngOut.c src/qrcodegen.c -o png

## RUN
```bash
echo "Hello world" | ./png