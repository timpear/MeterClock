/*
 * This will manually set the time on the Teensy RTC for testing
 * The time will begin when the meterclock sketch is uploaded and the Teesny reboots
 * To get the correct epoch code: http://www.epochconverter.com/
 * Run TimeTeensy3 (under File/examples/time in the Arduino IDE) to set current time from computer's system clock
 */

#include <Time.h>  

int t = 1387601970; // 4:59:30
//int t = 1387630770; // 12:59:30
//int t = 1387670370; // 23:59:30
//int t = 1387632243; // 13:24:03

void setup()  {
}

void loop() {
  Teensy3Clock.set(t);
  setTime(t);
}
