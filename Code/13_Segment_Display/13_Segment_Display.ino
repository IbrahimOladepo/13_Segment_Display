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
    {1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}  // 9

};


// Color pattern options
int colorPattern[7][3] = {
  {255, 0, 0},
  {0, 255, 0},
  {0, 0, 255},
  {150, 0, 255},
  {255, 200, 20},
  {85, 60, 180},
  {50, 255, 20}
};


// Display reset pattern
int offPattern[] = {0, 0, 0};


// Time to display 
int timeNow = 0;

// Color selector variable
int colorNow = 5;

// Color time display variable
int colorTime = 100;


// Init LEDs
CRGB leds_1[NUM_LEDS];    // RIGHT LED (UNIT)
CRGB leds_2[NUM_LEDS];    // LEFT LED (TENS)


// Function definitions
unsigned int digitCount(unsigned int i);     // Counts the number of digits in a given number


void setup() {
  
  // Initialize FastLED
  FastLED.addLeds<WS2812, LED_PIN_1, GRB>(leds_1, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_2, GRB>(leds_2, NUM_LEDS);

}


void loop() {

  // Count digits
  unsigned int digits = digitsCount(timeNow);

  // Loop through each digit
  // and turn on LEDs accordingly
  if (digits = 1){

    // Reset display
    for (int i = (NUM_LEDS - 1); i >= 0; i--){

      leds_1[i] = CRGB(offPattern[0], offPattern[1], offPattern[2]);
      FastLED.show();

    }
    
    // Turn on single display
    for (int i = 0; i < NUM_LEDS; i++){

      if (segmentPatterns[timeNow][i] == 1){

        leds_1[i] = CRGB(colorPattern[colorNow][0], colorPattern[colorNow][1], colorPattern[colorNow][2]);
        FastLED.show();
        delay(colorTime); 

      }

    }

  }
  else{

    // Splits digits through a loop
    char digitsArray[digits];
    while (digits--) {
      digitsArray[digits] = (timeNow % 10);
      timeNow /= 10;
    }

    // Turn on both displays
    // DISPLAY 1
    // Reset display
    for (int i = (NUM_LEDS - 1); i >= 0; i--){

      leds_1[i] = CRGB(offPattern[0], offPattern[1], offPattern[2]);
      FastLED.show();

    }

    for (int i = 0; i < NUM_LEDS; i++){

      if (segmentPatterns[digitsArray[0]][i] == 1){

        leds_1[i] = CRGB(colorPattern[colorNow][0], colorPattern[colorNow][1], colorPattern[colorNow][2]);
        FastLED.show();
        delay(colorTime); 

      }

    }

    // DISPLAY 2
    // Reset display
    for (int i = (NUM_LEDS - 1); i >= 0; i--){

      leds_2[i] = CRGB(offPattern[0], offPattern[1], offPattern[2]);
      FastLED.show();

    }

    for (int i = 0; i < NUM_LEDS; i++){

      if (segmentPatterns[digitsArray[1]][i] == 1){

        leds_2[i] = CRGB(colorPattern[colorNow][0], colorPattern[colorNow][1], colorPattern[colorNow][2]);
        FastLED.show();
        delay(colorTime); 

      }

    }

  }
  
  // Time increment
  timeNow = (timeNow + 1) % 24;
  delay(colorTime*5); 

}


// Code from: 
// https://stackoverflow.com/questions/9302681/c-how-to-break-apart-a-multi-digit-number-into-separate-variables
unsigned int digitsCount(unsigned int i) {
  
  unsigned int ret=1;
  while (i/=10) ret++;
  return ret;
}
