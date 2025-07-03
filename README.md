# Joke Machine — Arduino Project with TFT SPI Display

This project is a simple joke generator running on Arduino, displaying random jokes on a small TFT SPI display. Perfect for beginner makers who want to combine programming, electronics, and fun.

---

## Features

- Generates and displays random jokes (in Czech)
- Output on a color TFT SPI display
- Easy to modify and add new jokes in the code
- Uses the TFT_eSPI library (or other compatible library for your display)

---

## Hardware

- Arduino-compatible board (e.g. Arduino Uno, Mega, or ESP32)
- TFT SPI display (e.g. ILI9341, ST7735, or similar)
- Connected via SPI pins plus control pins as required by the library

---

## Software

- Arduino IDE
- [TFT_eSPI library](https://github.com/Bodmer/TFT_eSPI) or other compatible display library
- Source code in `sketch_jul01c.ino`

---

## Installation and Usage

1. Install the Arduino IDE if you don’t have it yet: [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)
2. Install the TFT_eSPI library via Arduino Library Manager or download from GitHub.
3. Configure the library for your specific TFT SPI display (check the library’s User Setup file).
4. Open `sketch_jul01c.ino` in Arduino IDE.
5. Connect your Arduino and TFT display hardware.
6. Upload the sketch to your Arduino board.
7. The device will show random jokes on the TFT display.

---

## Customization

- Edit the jokes list directly in the `sketch_jul01c.ino` file to add your own jokes.
- Modify display settings and fonts by adjusting the TFT_eSPI library configuration.

---

## License

This project is open source and free to use.

---

Feel free to ask if you want help with wiring, library setup, or code modifications!

