#include "13_Segment_Display.h"

int segmentPattern(char digit, char segmentPattern){

    char status = 0;

    if (digit < 0 || digit > 9) {
        status = -1;  // Return all LEDs off for invalid digit
    }
    else{

        // Set the segmentPattern pointer to the requested digit sequence address
        segmentPattern = segmentPatterns[digit];

        status = 1;   // Success status value 
    }


    return status;
}


