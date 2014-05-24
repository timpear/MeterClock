Meter Clock, written for the 60-pixel Adafruit NeoPixel strip.
by Tim Bartlett

V1 uses clock logic using delay(), and is set with a radial encoder / push-button. It loses time quickly.

V2 is written for a Teensy 3.0 or 3.1 (Arduino-compatible microcontroller board) with crystal soldered on, using the Arduino Time library.

V3 [UNTESTED!!! MAY NOT WORK] is the same as V2, but erases the entire clock every cycle instead of just the pixel that is to be turned off. This shortens the code quite a bit.

Links:

Adafruit NeoPixel strip: http://www.adafruit.com/products/1138
Teensy 3.0: http://www.pjrc.com/teensy/

NeoPixel library: https://github.com/adafruit/Adafruit_NeoPixel
Time library for Teensy: http://www.pjrc.com/teensy/td_libs_Time.html