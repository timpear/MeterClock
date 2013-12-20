// PixelStrip Clock
// original design by Tim Bartlett
// for 60 pixel strip and Teensy 3.0 with crystal

#include <Time.h>
#include <Adafruit_NeoPixel.h>
#define PIN 20

int sPrev; // previously displayed second, for clearing pixel
int mPrev;
int hPrev;
int hD; // hour number to display on a scale of 0-59

const int sR = 100;
const int sG = 100;
const int sB = 100;

const int mR = 25;
const int mG = 255;
const int mB = 255;

const int hR = 25;
const int hG = 25;
const int hB = 255;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  setSyncProvider(getTeensy3Time);
  mPrev = minute();
  hPrev = hour();
  strip.begin();
  strip.show();
}

void loop() { 
  previousSecond(second());
  previousMinute(minute());
  hourFormat(hour());
  previousHour(hD);

  strip.setPixelColor(hD, hR, hG, hB);
  strip.setPixelColor(minute(), mR, mG, mB);
  strip.setPixelColor(second(), sR, sG, sB);
       
  strip.show();
  delay(500);
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

void hourFormat(int h) {
   if (h < 12) {
    hD = h * 5;
  } else {
    hD = (h - 12) * 5;
  } 
}

void previousSecond(int s) {
  if (s == 0) {
    sPrev = 59; 
  } else {
    sPrev = s - 1;
  }  
  strip.setPixelColor(sPrev, 0, 0, 0);
}

void previousMinute(int m) {
  if (m == mPrev) {
  } else {
    strip.setPixelColor(mPrev, 0, 0, 0);
    mPrev = m;
  }
}

void previousHour(int h) {
  if (h == hPrev) {
  } else {
    strip.setPixelColor(hPrev, 0, 0, 0);
    hPrev = h;
  }
}
