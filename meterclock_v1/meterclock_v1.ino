// PixelStrip Clock
// original design by Tim Bartlett
// for 60 pixel strip and Teensy 3.0
// v1 sets with encoder, keeps time with delay()

// NOTE: this doesn't accurately keep time

#include <Adafruit_NeoPixel.h>
#include <Encoder.h>
#define PIN 3

const int BUTTON=4;
Encoder myEnc(5, 6);
boolean lastButton = LOW;
boolean currentButton = LOW;
boolean clockRun = false;

int hOrigin = 0; // set hour at boot
int mOrigin = 5; // set minute at boot

int sMin = 0;
int mMin = 0;
int hMin = 0;
int hD = 0;

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
  pinMode (BUTTON, INPUT);
  strip.begin();
  strip.show();
}

long oldPosition  = -999;

boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON);
  if (last != current)
  {
    delay(5);
    current = digitalRead(BUTTON);
  }
  return current;
}

void loop() {
// CLOCK SET

  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH) {
    clockRun = !clockRun;
  }
  
  lastButton = currentButton;
  
  if(clockRun == false){
    hD = hOrigin * 5;
    long newPosition = myEnc.read();
  
    if (newPosition > oldPosition){
      mOrigin++;
      if (mOrigin == 60){
        mOrigin = 0;
        hOrigin++;
      }  
      if (hOrigin == 12){
        hOrigin = 0;
      }
    }  
    else if (newPosition < oldPosition){
      mOrigin--;
      if (mOrigin < 0){
        mOrigin = 59;
        hOrigin--;
      }
      if (hOrigin < 0){
        hOrigin = 11;
      }     
    }
  
    if (newPosition != oldPosition) {
      oldPosition = newPosition;
      for (int clr = 0; clr < 60; clr++) {
        strip.setPixelColor(clr, 0, 0, 0);
      }
      strip.setPixelColor(0, 20, 0, 0);
      strip.setPixelColor(15, 20, 0, 0);
      strip.setPixelColor(30, 20, 0, 0);
      strip.setPixelColor(45, 20, 0, 0);
      
      strip.setPixelColor(hD, 255, 100, 0);
      strip.setPixelColor(mOrigin, 255, 255, 0);
      strip.show();     
    }   
  }
  else{      
//CLOCK RUN

    for (int clr = 0; clr < 60; clr++) {
      strip.setPixelColor(clr, 0, 0, 0);
    }
      
    for (int h = hOrigin; h < 12; h++) {
          
      if (h == 0) {
        hMin = 11; 
      } else {
        hMin = h - 1;
      }
          
      hD = h * 5;
      strip.setPixelColor(hMin * 5, 0, 0, 0);
      
      for (int m = mOrigin; m < 60; m++) {    
              
        if (m == 0) {
          mMin = 59; 
        } else {
          mMin = m - 1;
        } 
        strip.setPixelColor(mMin, 0, 0, 0);
            
        for (int s = 0; s < 60; s++) {
          if (s == 0) {
            sMin = 59; 
          } else {
            sMin = s - 1;
          } 
                  
          mOrigin = 0;
          hOrigin = 0;
                  
          strip.setPixelColor(sMin, 0, 0, 0);
//          strip.setPixelColor(0, 0, 0, 20);
//          strip.setPixelColor(15, 0, 0, 20);
//          strip.setPixelColor(30, 0, 0, 20);
//          strip.setPixelColor(45, 0, 0, 20);
          
          strip.setPixelColor(hD, hR, hG, hB);
          strip.setPixelColor(m, mR, mG, mB);
          strip.setPixelColor(s, sR, sG, sB);
       
          strip.show();
          delay(1000);
        }
      }     
    }
  }
}
