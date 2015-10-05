#include <Adafruit_NeoPixel.h>
#include <PixelPattern.h>

#define PIN 0

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_RGB + NEO_KHZ400);
PixelPattern pattern = PixelPattern();

char rgb[3];

void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  pixels.setBrightness(100); // 1/3 brightness

  rgb[0] = 0;
  rgb[1] = 0;
  rgb[2] = 0;

  pattern.cycle(10000);
}

void loop() {
  // put your main code here, to run repeatedly:
  pattern.loop(rgb);
  
  pixels.setPixelColor(0, rgb[0], rgb[1], rgb[2]);
  pixels.show();
   
}
