// PixelStrip Clock
// by Tim Bartlett
// for 60 pixel strip and Teensy 3.0 with crystal

#include <Time.h>
#include <Adafruit_NeoPixel.h>
#define PIN 20

// clockMode sets color scheme:
// 0=GRAY, 1=BLUES, 2=ORANGES, 3=GREENS, 4=CHRISTMAS
int clockMode = 1;
// faceMode sets dial reference points:
// 0=off, 1=every 15 minutes, 2=every 5 minutes
int faceMode = 2;
// hourChime adds blinky animation on the new hour, when true
boolean hourChime = true;

int sPrev;
int mPrev;
int hPrev;
int hD;
int twelveHour;
int lastTH;
int sR;
int sG;
int sB;
int mR;
int mG;
int mB;
int hR;
int hG;
int hB;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  setSyncProvider(getTeensy3Time);
  mPrev = minute();
  hourFormat(hour());
  hPrev = hD;
  lastTH = twelveHour;
  colorSelect(clockMode); // move to colorSelect input code below
  strip.begin();
  strip.show();
}

void loop() { 
  // put input here to set clockMode 
  // put input here to select faceMode
 
  eraseSecond();
  eraseMinute(minute()); //this may not be necessary with the new eraseSecond function
  hourFormat(hour());
  eraseHour(hD);
  setFace(faceMode);
  setClock();
  strip.show();
  delay(100);
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

void hourFormat(int h) {
  if (h == 0 || h == 12) {
    twelveHour = 12;
    hD = 0 + (minute() / 12);
  } 
  else if (h > 0 && h < 12) {
    twelveHour = h; 
    hD = (h * 5) + (minute() / 12);
  } 
  else {
    twelveHour = h - 12;
    hD = ((h - 12) * 5) + (minute() / 12);
  } 
}

void eraseSecond() {
  for (int i = 0; i < 60; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  } 
}

void eraseMinute(int m) {
  if (m != mPrev) {
    strip.setPixelColor(mPrev, 0, 0, 0);
    mPrev = m;
  } 
}

void eraseHour(int h) {
  if (h != hPrev) {
    strip.setPixelColor(hPrev, 0, 0, 0);
    hPrev = h;
  }
  
  if (twelveHour != lastTH && hourChime == false) {
    strip.setPixelColor(hPrev, 0, 0, 0);
    lastTH = twelveHour;
    hPrev = h;
  }
  else if (twelveHour != lastTH && hourChime == true) {
    for (int i = 0; i < twelveHour; i++) {
      for (int p = 0; p < 60; p++) {
        if (p <= h) {
          strip.setPixelColor(p, mR, mG, mB);
        }
        else {
          strip.setPixelColor(p, hR, hG, hB);
        }
        strip.show();
        delay(17);
      }     
      for (int p = 0; p < 60; p++) {
        strip.setPixelColor(p, 0, 0, 0);
        strip.show();
        delay(17);
      }   
    }
    strip.setPixelColor(hPrev, 0, 0, 0);
    lastTH = twelveHour;
    hPrev = h;
  }
  else {
  }
}

void setClock() {
  if (minute() == hD && second() == hD) {
    strip.setPixelColor(second(), 255, 255, 255);
  }
  else if (minute() == hD && second() != hD) {
    strip.setPixelColor(minute(), ((hR+mR)/2), ((hG+mG)/2), ((hB+mB)/2));
    strip.setPixelColor(second(), sR, sG, sB);
  }
  else if (second() == minute() && hD != minute()) {
    strip.setPixelColor(second(), ((sR+mR)/2), ((sG+mG)/2), ((sB+mB)/2));
    strip.setPixelColor(hD, hR, hG, hB);
  }
  else if (second() == hD && minute() != hD) {
    strip.setPixelColor(second(), ((sR+hR)/2), ((sG+hG)/2), ((sB+hB)/2));
    strip.setPixelColor(minute(), mR, mG, mB);
  }
  else {
    strip.setPixelColor(hD, hR, hG, hB);
    strip.setPixelColor(minute(), mR, mG, mB);
    strip.setPixelColor(second(), sR, sG, sB);
  }
}

void setFace(int ticks) {
  switch(ticks){
    case 0: //OFF
      break;
    
    case 1: //every 15 minutes
      strip.setPixelColor(0, (hR/50), (hG/50), (hB/50));
      strip.setPixelColor(15, (hR/50), (hG/50), (hB/50));
      strip.setPixelColor(30, (hR/50), (hG/50), (hB/50));
      strip.setPixelColor(45, (hR/50), (hG/50), (hB/50));
      break;
    
    case 2: //every 5 minutes
      strip.setPixelColor(0, (hR/50), (hG/50), (hB/50));
      strip.setPixelColor(5, (hR/50), (hG/50), (hB/50));
      strip.setPixelColor(10, (hR/50), (hG/50), (hB/50));
      strip.setPixelColor(15, (hR/50), (hG/50), (hB/50));
      strip.setPixelColor(20, (hR/50), (hG/50), (hB/50));
      strip.setPixelColor(25, (hR/50), (hG/50), (hB/50));
      strip.setPixelColor(30, (hR/50), (hG/50), (hB/50));
      strip.setPixelColor(35, (hR/50), (hG/50), (hB/50));
      strip.setPixelColor(40, (hR/50), (hG/50), (hB/50));
      strip.setPixelColor(45, (hR/50), (hG/50), (hB/50));
      strip.setPixelColor(50, (hR/50), (hG/50), (hB/50));
      strip.setPixelColor(55, (hR/50), (hG/50), (hB/50));  
  } 
}

void colorSelect(int mode) {
  switch(mode){
    case 0: //GRAY
      sR = 10;
      sG = 10;
      sB = 10;
      mR = 255;
      mG = 255;
      mB = 255;
      hR = 100;
      hG = 100;
      hB = 100;
      break;
      
    case 1: //BLUES
      sR = 100;
      sG = 100;
      sB = 100;
      mR = 25;
      mG = 255;
      mB = 255;
      hR = 25;
      hG = 25;
      hB = 255;
      break;
      
    case 2: //ORANGES
      sR = 100;
      sG = 100;
      sB = 100;
      mR = 255;
      mG = 255;
      mB = 0;
      hR = 255;
      hG = 100;
      hB = 0;
      break;
    
    case 3: //GREENS
      sR = 100;
      sG = 100;
      sB = 100;
      mR = 100;
      mG = 255;
      mB = 50;
      hR = 25;
      hG = 255;
      hB = 25;
      break;
      
    case 4: //CHRISTMAS
      sR = 100;
      sG = 100;
      sB = 100;
      mR = 255;
      mG = 0;
      mB = 0;
      hR = 0;
      hG = 255;
      hB = 0;
      break;      
  }
}
