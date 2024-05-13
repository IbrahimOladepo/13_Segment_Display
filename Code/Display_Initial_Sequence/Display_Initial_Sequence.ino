#include <FastLED.h>


#define LED_PIN     7
#define NUM_LEDS    13

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

// Color selector variable
int colorNow = 0;

// LED display delay time
int colorTime = 200;

CRGB leds[NUM_LEDS];


void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
}


void loop() {

  // On Sequence
  for (int i = 0; i < NUM_LEDS; i++){

    leds[i] = CRGB(colorPattern[colorNow][0], colorPattern[colorNow][1], colorPattern[colorNow][2]);
    FastLED.show();
    delay(colorTime); 

  }

  // Off Sequence
  for (int i = (NUM_LEDS - 1); i >= 0; i--){

    leds[i] = CRGB(offPattern[0], offPattern[1], offPattern[2]);
    FastLED.show();
    delay(colorTime); 

  }

  // Color selector increment
  colorNow = (colorNow + 1) % 7;

}