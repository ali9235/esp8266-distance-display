# Recorded software checks

Date: 15 October 2026. Newly authored reference code, not original recovered firmware.

| Check | Actual result |
| --- | --- |
| Standalone C++ core tests | 18 checks passed with MSVC C++17, /W4 /WX |
| Arduino default sketch | Compilation passed; hardware-disabled configuration |
| Optional adapter branches | Compilation passed using private compiler-only fixture configuration |
| Reference target | NodeMCU v2 / esp8266:esp8266:nodemcuv2 / core 3.1.2 |
| Physical hardware / electrical validation | Not performed |

Fixture pins are not electrical recommendations and are not included as a public wiring map. No firmware was flashed. Successful compilation does not establish sensor accuracy, joystick response, display behavior, charging safety or unattended reliability. The original photograph is not a demonstration of this code version.

[Build instructions and limitations](FIRMWARE.md) · [Actual core test source](tests/test_core.cpp)
