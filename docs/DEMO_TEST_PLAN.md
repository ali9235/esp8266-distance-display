# Echo: measure against a reference

**Status: planned, not performed.** A sensor photograph and a compiled sketch are not an accuracy dataset.

## Setup gate

Complete [WIRING_AND_SOURCE.md](../WIRING_AND_SOURCE.md): exact module, interface, ratings, safe echo-level conversion if required, actual board and TFT driver. Do not connect an unidentified echo output directly to the MCU. Disconnect power before changing wiring. Do not substitute private compiler fixture GPIOs for a real schematic.

Choose stationary reference distances within the **identified** sensor's documented operating range. State the measurement origin, target material/angle, ambient conditions, sample count and acceptable error before collecting data. The sketch's example 2–400 cm window is not a sensor rating.

## A useful 60–90 second recording

1. Show the module markings, ruler/reference arrangement, code revision and whether mode is `SENSOR` or `SIMULATION`.
2. Keep the stationary target, reference and output in view. Show repeat samples at more than one preselected distance.
3. Show no-echo or invalid behavior using a safe target change—not live rewiring—and then recovery after enough fresh samples.
4. State the actual error/limits. Do not claim safe obstacle detection or use the device for navigation on this evidence.

## Bench cases

| ID | Test | Data to keep | Acceptance basis |
| --- | --- | --- | --- |
| E1 | Stationary reference distances | Reference, raw observations, displayed result and units | Error tolerance and sample count chosen before testing |
| E2 | Repeated readings at one target | Raw series, median, spread and conditions | Show spread honestly; do not hide outliers |
| E3 | No echo / stale input | Invalid indication and timing/recovery evidence | Timeout is not displayed as a valid zero; compare to recorded policy |
| E4 | Hysteresis transition | Movement direction, reference and state changes | Compare to configured thresholds; not a safety guarantee |

Use [hardware-observations.csv](../tests/hardware-observations.csv), adding rows for repeated samples. Every template row is `not_run`. Reference and observed numeric fields remain blank until measured. If calculating error later, preserve the original inputs and state the method.

## Be ready to explain

Why divide by two? What does the median help with, and what does it not fix? Why separate invalid from zero? What happens when data stop? Where is the physical echo voltage documented? The most credible demonstration includes a limitation and a failed case.
