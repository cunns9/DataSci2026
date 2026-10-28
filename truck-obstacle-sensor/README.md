# RC Truck Obstacle Sensor

An ultrasonic obstacle detector for a toy RC construction truck, built on an ESP32-S3. The board's built-in RGB LED shows how close the nearest object is.

Part of my Mathematics for Data Science final project: AlexNet learns to recognize the lab's construction trucks, and later a computer drives them. This sensor is the first piece of hardware for the "computer drives a truck" stage.

## Status (2026-10-27)

The board and code work. The first upload succeeded and the LED runs. The sensor doesn't fire yet because the board's 5V pin is off until the **IN-OUT** pads are soldered together. Details are in the [build log](build-log.md).

**Pick up here:**
1. Solder the IN-OUT pads (between pins 11 and 10) together.
2. Unplug USB, then move the power wire from **3V3** back to **5V**.
3. Move the GPIO 5 wire from **row 10** back to **row 14** (the divider's middle row). Echo at 5V straight into GPIO 5 can damage the board.
4. Re-upload `truck_obstacle_sensor.ino`. The board currently has `echo_debug` on it.
5. Test with a book: green → yellow → red.

## Parts

| Part | Notes |
|---|---|
| ESP32-S3-N16R8 dev board | Two USB-C ports (COM/UART and USB) |
| HC-SR04 ultrasonic sensor | Runs on 5V; range about 1 in to 13 ft |
| Half-size breadboard | |
| Jumper wires | Female-to-male for the board's header pins |
| 3 × 33K ohm resistors | Voltage divider on the Echo line |

## Wiring

| From | To |
|---|---|
| ESP32 5V | Breadboard + rail |
| ESP32 GND | Breadboard − rail |
| Sensor VCC | + rail |
| Sensor GND | − rail |
| Sensor Trig | ESP32 GPIO 4 |
| Sensor Echo | Voltage divider → ESP32 GPIO 5 |

### Why the voltage divider

The HC-SR04 sends its Echo signal back at 5V, but ESP32 pins are 3.3V only. Three equal resistors split the voltage down:

```
Sensor ECHO ──[33K]──┬── ESP32 GPIO 5
                     │
                  [33K]
                     │
                  [33K]
                     │
                    GND
```

Vout = 5V × 66K / (33K + 66K) ≈ 3.3V

## How it works

1. The ESP32 sets Trig high for 10 µs, which makes the sensor send out an ultrasonic ping.
2. It times how long Echo stays high, which is the round trip of the sound.
3. distance = time × speed of sound (0.0343 cm/µs) ÷ 2, then converted to feet.
4. It repeats every 100 ms.

| LED | Meaning |
|---|---|
| Dim blue | Starting up |
| Green | Nothing within 5 ft |
| Yellow | Object 1–5 ft away |
| Red | Object closer than 1 ft |

The distance also prints to the Serial Monitor at 115200 baud.

## Upload

1. Arduino IDE → Board: **ESP32S3 Dev Module**.
2. Plug into the **COM/UART** USB-C port. (On the **USB** port, set *Tools → USB CDC On Boot → Enabled* or Serial stays blank.)
3. Open `truck_obstacle_sensor/truck_obstacle_sensor.ino` and upload.
4. Open Serial Monitor at 115200 and move a hand toward the sensor.

## Troubleshooting

- **Always green / `echo_debug` says NO ECHO:** the sensor has no power. On this board, the 5V pin needs the IN-OUT pads bridged with solder. The HC-SR04 doesn't fire on 3.3V.

- **LED doesn't light:** change `RGB_BUILTIN` from 48 to 38. The pin depends on the board version.
- **`neopixelWrite` won't compile:** newer ESP32 board packages renamed it `rgbLedWrite`.
- **Always green:** if no echo comes back (for example, a loose Echo wire), the code treats it as "clear." Check the Echo and divider wiring.

## Next steps

- Mount the sensor on a truck.
- Wire an Arduino to the truck's remote so the computer can stop the truck when the LED would turn red.

## Build log

See [build-log.md](build-log.md).
