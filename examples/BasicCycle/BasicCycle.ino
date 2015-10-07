#include <Adafruit_NeoPixel.h>
#include <PixelPattern.h>

#define PIN 0

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_RGB + NEO_KHZ400);
PixelPattern pattern = PixelPattern();

RGB rgb;

void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  pixels.setBrightness(100); // 1/3 brightness

  rgb.r = rgb.g = rgb.b = 0;
  
  pattern.cycle(10000);
}

void loop() {
  // put your main code here, to run repeatedly:
  rgb = pattern.loop();
  
  pixels.setPixelColor(0, rgb.r, rgb.g, rgb.b);
  pixels.show();
   
}
