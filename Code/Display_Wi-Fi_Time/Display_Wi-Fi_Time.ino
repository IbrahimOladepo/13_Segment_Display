// Some code sources:
// https://lastminuteengineers.com/esp32-ntp-server-date-time-tutorial/
// // https://randomnerdtutorials.com/esp32-ntp-client-date-time-arduino-ide/
// https://stackoverflow.com/questions/9302681/c-how-to-break-apart-a-multi-digit-number-into-separate-variables


#include <WiFi.h>
#include "time.h"
#include <FastLED.h>


// Define Arduino pin connections
#define LED_PIN_1     22
#define LED_PIN_2     23

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
// int timeNow = 0;

// Color selector variable
// int colorNow = 4;

// Color time display variable
int colorTime = 20;

const char* ssid     = "FILL-IN-SSID";
const char* password = "FILL-IN-PASSWORD";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -18000;
const int   daylightOffset_sec = 0;

// Time info structure init
struct tm timeinfo;


// Function definitions
unsigned int digitCount(unsigned int i);     // Counts the number of digits in a given number
void printLocalTime(struct tm &timeinfo);
void LEDDisplay(int timeNow);


// Init LEDs
CRGB leds_1[NUM_LEDS];    // RIGHT LED (UNIT)
CRGB leds_2[NUM_LEDS];    // LEFT LED (TENS)


void setup()
{
  Serial.begin(115200);
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("WI-FI CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime(timeinfo);

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  // Initialize FastLED
  FastLED.addLeds<WS2812, LED_PIN_1, GRB>(leds_1, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_2, GRB>(leds_2, NUM_LEDS);

  // Reset displays
  for (int i = (NUM_LEDS - 1); i >= 0; i--){

    leds_1[i] = CRGB(offPattern[0], offPattern[1], offPattern[2]);
    leds_2[i] = CRGB(offPattern[0], offPattern[1], offPattern[2]);
    FastLED.show();
    delay(colorTime);

  }
  delay(5000);

}


void loop(){

  // delay(10000);
  printLocalTime(timeinfo);

  Serial.println(timeinfo.tm_hour);
  Serial.println(timeinfo.tm_min);
  Serial.println();

  // Display hour
  LEDDisplay(timeinfo.tm_hour, 3);
  FastLED.show();
  delay(5000); 

  // Display minute
  LEDDisplay(timeinfo.tm_min, 4);
  FastLED.show();
  delay(5000); 

}


unsigned int digitsCount(unsigned int i) {
  
  unsigned int ret=1;
  while (i/=10) ret++;
  
  return ret;

}


void printLocalTime(struct tm &timeinfo){
  
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }

  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}


void LEDDisplay(int timeNow, int colorNow){

  // Print time now
  Serial.print(timeNow);
  Serial.print(", ");

  // Count digits
  unsigned int digits = digitsCount(timeNow);
  Serial.println(digits);

  // Loop through each digit
  // and turn on LEDs accordingly
  if (digits == 1){

    // Reset displays
    for (int i = (NUM_LEDS - 1); i >= 0; i--){

      leds_1[i] = CRGB(offPattern[0], offPattern[1], offPattern[2]);
      leds_2[i] = CRGB(offPattern[0], offPattern[1], offPattern[2]);
      // FastLED.show();
      // delay(colorTime);

    }
    
    // Turn on single display
    for (int i = 0; i < NUM_LEDS; i++){

      if (segmentPatterns[timeNow][i] == 1){

        leds_1[i] = CRGB(colorPattern[colorNow][0], colorPattern[colorNow][1], colorPattern[colorNow][2]);
        // FastLED.show();
        delay(colorTime); 

      }
      if (segmentPatterns[0][i] == 1){
        // Set second display to zero
        leds_2[i] = CRGB(colorPattern[colorNow][0], colorPattern[colorNow][1], colorPattern[colorNow][2]);
        delay(colorTime); 
      }

    }

  }

  if (digits == 2){

    // Splits digits through a loop
    char digitsArray[digits];
    int temp = timeNow;

    while (digits--) {
      digitsArray[digits] = (temp % 10);
      temp /= 10;
    }

    // Reset displays
    for (int i = (NUM_LEDS - 1); i >= 0; i--){

      leds_1[i] = CRGB(offPattern[0], offPattern[1], offPattern[2]);
      leds_2[i] = CRGB(offPattern[0], offPattern[1], offPattern[2]);
      // FastLED.show();
      // delay(colorTime);

    }

    // Turn on both displays
    for (int i = 0; i < NUM_LEDS; i++){

      if (segmentPatterns[digitsArray[1]][i] == 1){
        leds_1[i] = CRGB(colorPattern[colorNow][0], colorPattern[colorNow][1], colorPattern[colorNow][2]);
      }

      if (segmentPatterns[digitsArray[0]][i] == 1){
        leds_2[i] = CRGB(colorPattern[colorNow][0], colorPattern[colorNow][1], colorPattern[colorNow][2]);
      }

      // FastLED.show();
      delay(colorTime);

    }

  }

}