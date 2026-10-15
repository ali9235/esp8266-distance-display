# New reference distance firmware

New code, **not the original firmware behind the photograph**. Physical measurements and the actual sensor/display model remain unverified.

## Source

[Arduino adapter](firmware/distance_display/distance_display.ino) · [Portable filter](firmware/distance_display/distance.h) · [Configuration](firmware/distance_display/config.h) · [Core tests](tests/test_core.cpp)

The new logic rejects zero-duration/time-out pulses, rejects values outside a configurable-by-source example 2–400 cm window, requires three fresh samples, and applies a rolling median of up to five samples. Values expire after one second; new samples cannot resurrect an expired history. A near indicator uses 30/35 cm hysteresis. These are example settings, **not a specified range/accuracy or a navigation safety boundary**. Conversion assumes approximately 343 m/s sound speed and is not temperature-compensated.

## Build the serial-only default

Reference target: NodeMCU 1.0 / ESP8266, core **3.1.2**. The physical board revision remains unconfirmed.

```powershell
arduino-cli compile --fqbn esp8266:esp8266:nodemcuv2 firmware/distance_display
```

Inputs and TFT are disabled by default, with unset GPIOs. No generated sample is labelled a measurement. If deliberately flashed later, serial input at 115200 baud accepts `n` for an explicitly simulated near pulse, `l` for a simulated far pulse, and `f` for a timeout. Send at least three samples within one second to produce a valid filtered simulation. Output says `SIMULATION` unless the physical input adapter is enabled.

## Optional hardware adapter

The adapter supports a **trigger/echo pulse interface** only; other range modules require a different driver. It uses a 30,000-microsecond timeout, with nominal 200 ms sampling and a cooperative main loop. Never display a timeout as a valid zero-centimetre measurement. See Arduino's [pulseIn reference](https://docs.arduino.cc/language-reference/en/functions/advanced-io/pulseIn/).

The optional renderer is specifically a **new ST7735 black-tab 128×160 reference**, not an identification of the pictured display. Compile with Adafruit ST7735/ST7789 1.11.0, GFX 1.12.6 and BusIO 1.17.4 after confirming the actual module, power/logic requirements, reset and SPI wiring. Change the driver if its real controller differs. Full-screen redraw is intentionally simple; flicker and refresh speed require device evaluation.

GPIOs remain unset. Check echo voltage, suitable level conversion where required, shared grounds, SPI/control-pin conflicts, serial pins, and ESP8266 boot-strapping restrictions before enabling anything. Compiler-only fixture pin assignments used by the audit are **not wiring recommendations**.

## Standalone logic tests

```powershell
g++ -std=c++17 -Wall -Wextra -Werror tests/test_core.cpp -o test_core.exe
.\test_core.exe
```

Tests exercise the actual filter, median behavior, timeout/range rejection, freshness and clock rollover. They do not establish sensor precision or working TFT hardware. See [the actual-connection checklist](WIRING_AND_SOURCE.md).
