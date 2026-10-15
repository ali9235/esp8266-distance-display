# Source and connection checklist

This is an independent project, as confirmed by its owner. The original sketch was not found; [new reference firmware](FIRMWARE.md) is now included at the owner's request. It does not establish the pictured wiring or sensor/display identity.

| Signal group | Visible / known | Missing detail |
| --- | --- | --- |
| Range module | Two transducers and wired header | Exact model, output interface, supply/logic requirements, connected pins |
| TFT | 1.8-inch 128×160-labelled module | Controller, power rail, signal map and library |
| Controller | LoLin ESP8266-format board | Exact revision and firmware board target |
| Displayed measurement | Photograph reads 0 cm | Units in source, timeout handling, validity rules and reference test |

No direct echo-to-GPIO wiring is recommended without identifying the sensor and electrical interface. Provide the actual connection table or clear schematic. Keep no-echo/invalid states distinct from a valid measured zero; this is a verification requirement, not a claim about what the existing code already does.

## Detailed new-reference connection workflow

1. Identify the range module's exact model and interface. This adapter expects separate trigger/echo signals. UART, I2C and other sensors need their own driver; visual similarity is not sufficient.
2. Establish the module supply, echo output voltage and the actual ESP8266 board's input requirements. Add an appropriate verified level-conversion interface when needed; do not connect an unverified echo voltage directly to a GPIO.
3. Trace trigger, echo and the required ground reference. Enter the confirmed MCU pins in `TRIGGER_PIN` and `ECHO_PIN`, not display labels or wire colours. Set `RANGE_INTERFACE_VERIFIED` only after checking these electrical details.
4. Identify the TFT driver and power/logic specifications. This renderer targets ST7735 black-tab 128×160. Establish hardware SPI and actual CS/DC/reset wiring, then fill `TFT_CS`, `TFT_DC` and `TFT_RST`. Confirm the reset arrangement before setting its acknowledgement flag.
5. Check the entire allocation, including SPI bus pins, range signals, serial signals and boot-strapping requirements. The simple compile guards detect only some conflicts. Recheck GPIO behavior after every library initializes; do not copy private compiler-test pin assignments.
6. Start with both adapters disabled and run serial simulation. Enable the range adapter alone, inspect raw pulses and validity, then connect/enable the display after measurements are understood. Never interpret `NO VALID READING` or `NO ECHO` as a valid zero-centimetre result.
7. Compare several stationary known distances and include no-target, disconnected and out-of-range cases. Record raw pulse time, filtered result, reference distance and conditions. Example filter thresholds and the sound-speed approximation are not a calibrated sensor specification.

| New-code field | Connection meaning |
| --- | --- |
| `TRIGGER_PIN` | MCU output to the verified module's trigger input |
| `ECHO_PIN` | Verified, electrically compatible echo signal to MCU input |
| `TFT_CS` / `TFT_DC` | Confirmed display control inputs |
| `TFT_RST` | Actual reset signal, or -1 only with a verified alternate reset arrangement |

Exact physical GPIOs and a power circuit remain unresolved; this is an explicit commissioning guide, not a claim that the photographed circuit has been reverse-engineered.
