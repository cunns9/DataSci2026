# Build Log

## 2026-10-27

- Wrote the first sketch: HC-SR04 distance → RGB LED (green / yellow / red).
- Gathered the parts at home: ESP32-S3-N16R8, HC-SR04, breadboard, jumpers, 33K resistors. The trucks are still in the lab.
- Planned the Echo voltage divider with three 33K resistors (5V → about 3.3V).
- Installed Arduino IDE 2.3.10 and the "esp32 by Espressif Systems" 3.3.12 board package.
- Board: ESP32S3 Dev Module on port `/dev/cu.usbmodem…`. First upload worked, and the onboard LED lights up.
- Wired the sensor. The LED stayed green whatever was in front of the sensor (green = "no echo").
- Found the cause: this board's 5V pin is off until the **IN-OUT** pads (next to pins 11/10) are bridged with solder, so the sensor had no power.
- Tried running the sensor on 3V3, with Echo going straight to GPIO 5. `echo_debug` printed `idle=0 pulse=0 -> NO ECHO` on every ping, so the sensor doesn't fire at 3.3V and needs 5V.
- Next: solder the IN-OUT pads, move power back to 5V, and move the GPIO 5 wire back to the divider's middle row.
