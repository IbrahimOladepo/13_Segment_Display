#ifndef _13_SEGMENT_DISPLAY_H
#define _13_SEGMENT_DISPLAY_H

#include <Arduino.h>

#define NUM_LEDS    13
#define DIGIT       10

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

int segmentPattern(char digit, char segmentPattern);

#endif