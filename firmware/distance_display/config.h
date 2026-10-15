#pragma once
#define ENABLE_RANGE_INPUT 0
#define TRIGGER_PIN -1
#define ECHO_PIN -1
#define RANGE_INTERFACE_VERIFIED 0
#define ENABLE_TFT 0
#define TFT_CS -1
#define TFT_DC -1
#define TFT_RST -1
#define TFT_RESET_WIRING_VERIFIED 0
#define TFT_MODEL_VERIFIED 0
#if ENABLE_RANGE_INPUT && (TRIGGER_PIN < 0 || ECHO_PIN < 0 || TRIGGER_PIN == ECHO_PIN || !RANGE_INTERFACE_VERIFIED)
#error "Confirm actual sensor, pins, supply and safe echo logic level before enabling"
#endif
#if ENABLE_TFT && (TFT_CS < 0 || TFT_DC < 0 || !TFT_MODEL_VERIFIED || !TFT_RESET_WIRING_VERIFIED)
#error "Reference renderer uses ST7735 black-tab 128x160; verify actual module, reset and wiring"
#endif
#if ENABLE_TFT && (TFT_CS == TFT_DC || (TFT_RST >= 0 && (TFT_RST == TFT_CS || TFT_RST == TFT_DC)))
#error "TFT control pins must be distinct"
#endif
#if ENABLE_TFT && ENABLE_RANGE_INPUT && (TRIGGER_PIN == TFT_CS || TRIGGER_PIN == TFT_DC || TRIGGER_PIN == TFT_RST || ECHO_PIN == TFT_CS || ECHO_PIN == TFT_DC || ECHO_PIN == TFT_RST)
#error "Range and TFT control pins overlap"
#endif
