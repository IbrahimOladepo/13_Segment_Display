#include <FastLED.h>


#define LED_PIN     7
#define NUM_LEDS    12

int LEDPattern[LED_PIN] = {0, 2, 4, 6, 8, 10, 11};

int colorPattern[7][3] = {
  {255, 0, 0},
  {0, 255, 0},
  {0, 0, 255},
  {150, 0, 255},
  {255, 200, 20},
  {85, 60, 180},
  {50, 255, 20}
};

int offPattern[] = {0, 0, 0};

CRGB leds[NUM_LEDS];


void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
}


void loop() {
  
  for (int i = 0; i < LED_PIN; i++){

    leds[LEDPattern[i]] = CRGB(colorPattern[i][0], colorPattern[i][1], colorPattern[i][2]);
    FastLED.show();
    delay(500); 

  }

  leds[0] = CRGB(128, 0, 0);
  FastLED.show();
  delay(500);  

  leds[1] = CRGB(0, 128, 0);
  FastLED.show();
  delay(500);

  leds[2] = CRGB(0, 0, 128);
  FastLED.show();
  delay(500);

  leds[5] = CRGB(150, 0, 128);
  FastLED.show();
  delay(500);

  leds[7] = CRGB(128, 200, 20);
  FastLED.show();
  delay(500);

  leds[9] = CRGB(85, 60, 180);
  FastLED.show();
  delay(500);

  leds[11] = CRGB(50, 128, 20);
  FastLED.show();
  delay(500);

}