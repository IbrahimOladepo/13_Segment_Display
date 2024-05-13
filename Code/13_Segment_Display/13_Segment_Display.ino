#include <FastLED.h>


// Define Arduino pin connections
#define LED_PIN_1     7
#define LED_PIN_2     8

// Define LED and digit parameters
#define NUM_LEDS    13
#define DIGIT       10


// Define LED display pattern for each digit
const char segmentPatterns[DIGIT][NUM_LEDS] = {

  // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1}, // 0
    {1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0}, // 1
    {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1}, // 2
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0}, // 3
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}, // 4
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // 5
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 3, 0, 0, 0, 1, 1, 1, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}  // 9

};


// Time to display 
int timeNow = 0;


// Init LEDs
CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];


// Function definitions
unsigned int count(unsigned int i);


void setup() {
  
  // Initialize FastLED
  FastLED.addLeds<WS2812, LED_PIN_1, GRB>(leds_1, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_2, GRB>(leds_2, NUM_LEDS);

}


void loop() {
  
  // Time increment
  timeNow = (timeNow + 1) % 24;

}


unsigned int count(unsigned int i) {
  
  unsigned int ret=1;
  while (i/=10) ret++;
  return ret;
}
