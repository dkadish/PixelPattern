#include <Adafruit_NeoPixel.h>

#define PIN 0

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_RGB + NEO_KHZ400);

char rgb[3];
long duration, startTime;

void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  pixels.setBrightness(100); // 1/3 brightness

  rgb[0] = 0;
  rgb[1] = 0;
  rgb[2] = 0;

  startTime = millis();
  duration = 1000;
}

void loop() {
  // put your main code here, to run repeatedly:
  if( cycleFraction(startTime, duration) < 1.0 ){
    
  } else {
    rgb[0] = 0;
    rgb[1] = 0;
    rgb[2] = 0;
  }
  
  pixels.setPixelColor(0, rgb[0], rgb[1], rgb[2]);
  pixels.show();
   
}

