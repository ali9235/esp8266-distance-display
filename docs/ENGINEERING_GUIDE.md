# Echo: understand a reading before trusting it

This describes the new ranging reference, **not** the missing original sketch behind the photographed `0 cm` screen. That zero is not evidence of a correct distance measurement.

## The data path

A compatible trigger/echo sensor adapter obtains pulse duration. `Filter::push` converts the duration, validates it and updates a small median history. `Filter::read` returns a fresh valid reading or an invalid state. The sketch presents the result in serial output and, if separately verified, on the optional TFT.

| Visible part | Intended purpose | Unknown |
| --- | --- | --- |
| Dual-transducer module | Range sensing | Model, interface, supply and echo voltage |
| ESP8266 development board | Run the filtering/display application | Exact board revision and original pin map |
| 128×160-labelled TFT | Present status/distance | Driver and actual wiring |
| Breadboard/jumpers/USB | Prototype connections and USB link | Complete power/signal path |

The hardware-selection history is not available. Wi-Fi is not implemented in this reference and must not be advertised as an existing feature.

## Source walkthrough

| Source | Names | Read for |
| --- | --- | --- |
| [config.h](../firmware/distance_display/config.h) | Adapter switches and interface guards | Disabled-by-default hardware; guards do not prove safe voltage |
| [distance.h](../firmware/distance_display/distance.h) | `Filter::push` | Conversion, rejection, sample count, median and hysteresis |
| [distance.h](../firmware/distance_display/distance.h) | `read`, `clear` | Freshness and clearing invalid history |
| [distance_display.ino](../firmware/distance_display/distance_display.ino) | `loop`, `pulseIn` | Explicit simulation or optional physical pulse acquisition |
| [test_core.cpp](../tests/test_core.cpp) | `CHECK` | Real logic tests, not measured sensor accuracy |

## Five decisions worth understanding

1. Conversion is `pulseUs * 0.0343 / 2`: a reference sound-speed assumption in cm per microsecond and a round trip. It is not calibrated or temperature-compensated.
2. Zero-duration/timeouts and the example outside-2–400-cm values clear the history. This software window is **not** the identified sensor's rated range.
3. At least three fresh samples are needed; a rolling median uses up to five. This reduces isolated numerical outliers but cannot correct every physical measurement failure.
4. A reading expires at one second. Fresh data cannot resurrect an already expired history; three new samples are required.
5. The near state turns on below 30 cm and off at 35 cm or more. These are reference hysteresis values, not a navigation or safety boundary.

## Build and explicit simulation

```powershell
arduino-cli compile --fqbn esp8266:esp8266:nodemcuv2 firmware/distance_display
```

Both default and private adapter-only compilation passed again on 16 October 2026. No firmware was uploaded or physical range measured. See [FIRMWARE.md](../FIRMWARE.md) and historical [BUILD_STATUS.md](../BUILD_STATUS.md).

If a verified board is deliberately flashed later in default mode, serial keys `n`, `l`, `f` mean **simulated** near pulse, far pulse and timeout. At least three samples must arrive within one second. Output is labelled `SIMULATION`. This is not a desktop program and does not require or prove live ultrasonic reception.

## Exercises and diagnosis

- Hand-trace the existing test with two short pulses and one long pulse. Predict why the median remains near the short value.
- Explain what happens at exactly 1000 ms, not just after 1001 ms.
- In a software-only branch, add tests around the 30/35 cm hysteresis boundaries. Do not change physical enablement or claim sensor accuracy from the test.

| Symptom | First check |
| --- | --- |
| No valid result | Fewer than three fresh valid samples, timeout or expiry |
| Zero on original screen | Original program behavior unknown; do not call zero a valid echo |
| Bad physical values | Identify module/interface, safe logic levels, target geometry and reference method |
| Median seems delayed | Inspect history and sampling, then measure actual response |
| TFT fails but serial works | Confirm the real driver, power and traced display connections |

Never bypass an OS restriction to execute tests. Use the [bench plan](DEMO_TEST_PLAN.md) to establish actual performance and preserve raw observations.
