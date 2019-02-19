#include <FastLED.h>

#define LED_PIN  3 // Connect the data wire from your LED strip to this pin. Use a resistor!

#define COLOR_ORDER GRB
#define CHIPSET     WS2812B
#define NUM_LEDS    150 // Edit this to reflect the number of LEDS you are using.
#define BRIGHTNESS 32 // 0 to 255 - https://github.com/FastLED/FastLED/wiki/FastLED-Temporal-Dithering, https://github.com/FastLED/FastLED/wiki/Power-notes
CRGB leds[NUM_LEDS];

// Params for width and height, edit these to reflect your setup.
const uint8_t NumberOfColumns = 15; // Make sure this matches the number in the 'LightEmUp', 'CustomDrawColor', and 'CustomDrawMatrix' functions.
const uint8_t NumberOfRows = 10;

// Param for different pixel layouts, edit it to match your layout.
const bool    kMatrixSerpentineLayout = true;
// Set 'kMatrixSerpentineLayout' to false if your pixels are 
// laid out all running the same way, like this:
//
//     0 >  1 >  2 >  3 >  4
//                         |
//     .----<----<----<----'
//     |
//     5 >  6 >  7 >  8 >  9
//                         |
//     .----<----<----<----'
//     |
//    10 > 11 > 12 > 13 > 14
//
// Set 'kMatrixSerpentineLayout' to true if your pixels are 
// laid out back-and-forth, like this:
//
//     0 >  1 >  2 >  3 >  4
//                         |
//                         |
//     9 <  8 <  7 <  6 <  5
//     |
//     |
//    10 > 11 > 12 > 13 > 14
//                        |
//                        |
//    19 < 18 < 17 < 16 < 15


void setup() {
  delay( 3000 );
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(BRIGHTNESS);
}

// This function will return the right 'led index number' for 
// a given set of X and Y coordinates on your matrix.  
uint16_t XY( uint8_t row, uint8_t column)
{
  uint16_t i;
  
  if( kMatrixSerpentineLayout == false) {
    i = (row * NumberOfColumns) + column;
  }

  if( kMatrixSerpentineLayout == true) {
    if(row & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (NumberOfColumns - 1) - column;
      i = (row * NumberOfColumns) + reverseX;
    } else {
      // Even rows run forwards
      i = (row * NumberOfColumns) + column;
    }
  }

  i = i-1; // Shifts each LED by number specified.
  i = ((2*NUM_LEDS)+i)%NUM_LEDS; // If you try to assign more LEDs than defined, this wraps them back to the front
  return i;
}

// The 'LightEmUp' function uses the ColorMap matrix to assign the user
// defined colors to the corresponding pixel.
// Once assigned the LEDS are all turned on at once.
// Edit number of columns here ----\/ also
void LightEmUp(uint8_t *ColorMap[][15])
{
  // Loop through matrix.
  for(uint8_t column = 0; column < NumberOfColumns; column++) {
    for(uint8_t row = 0; row < NumberOfRows; row++) {
      // Set Color and get the LED index number using the 'XY' function.
      leds[XY(row, column)] = CRGB(*(ColorMap[row][column]),*((ColorMap[row][column])+1),*((ColorMap[row][column])+2));  
      }
    }
  FastLED.show();
}

// The 'Change1LED' function will assign the specified color to the
// LED at the coordinates provided and then show it.
void Change1LED(uint8_t row, uint8_t column, uint8_t *color)
{
  // Set Color and get the LED index number using the 'XY' function.
  leds[XY(row, column)] = CRGB(*color,*(color+1),*(color+2));
  FastLED.show();
}

// The 'CustomDrawColor' function will light up LEDS in the user specified order
// defined by a matrix of numbers, and waits an amount of time between each step.
// This lights the LEDs in a single color entered by the user.
// Edit column number here ---------\/ also
void CustomDrawColor(uint8_t Draw[][15], uint8_t *color, uint8_t wait)
{
  uint8_t loopmax = NUM_LEDS;
  uint8_t imax = 1;
  
  for (uint8_t i = 1; i <= loopmax; i++) {
    for(uint8_t column = 0; column < NumberOfColumns; column++) {
      for(uint8_t row = 0; row < NumberOfRows; row++) {
        // Find max value of the matrix, only do this once.
        if (Draw[row][column] >= imax & i == 1) {
          imax = Draw[row][column];
        }

        // Change the LED color during its specified turn.
        if (Draw[row][column] == i) {
          // Set Color and get the LED index number using the 'XY' function.
          leds[XY(row, column)] = CRGB(*color,*(color+1),*(color+2));
        }
      }
    }
    // Shorten length of for loop if maximum size not met.
    if (i == 1 && imax <= NUM_LEDS) {
      loopmax = imax;
    }
    FastLED.show();
    delay(wait);
  }
}

// The 'CustomDrawMatrix' is identical to 'CustomDrawColor' except it 
// lights each LED according to the color matrix entered by the user.
// Edit column number here ----------\/ and here -------------\/ also
void CustomDrawMatrix(uint8_t Draw[][15], uint8_t *ColorMap[][15], uint8_t wait)
{
  uint8_t loopmax = NUM_LEDS;
  uint8_t imax = 1;
  
  for (uint8_t i = 1; i <= loopmax; i++) {
    for(uint8_t column = 0; column < NumberOfColumns; column++) {
      for(uint8_t row = 0; row < NumberOfRows; row++) {
        // Find max value of the matrix, only do this once.
        if (Draw[row][column] >= imax & i == 1) {
          imax = Draw[row][column];
        }

        // Change the LED color during its specified turn.
        if (Draw[row][column] == i) {
          // Set Color and get the LED index number using the 'XY' function.
          leds[XY(row, column)] = CRGB(*(ColorMap[row][column]),*((ColorMap[row][column])+1),*((ColorMap[row][column])+2));
        }
      }
    }
    // Shorten length of for loop if maximum size not met.
    if (i == 1 && imax <= NUM_LEDS) {
      loopmax = imax;
    }
    FastLED.show();
    delay(wait);
  }
}

// Demo is below.
void loop()
{
    // Create and Edit color definitions here.
    // Use RGB values and the format: 'Variable'[3] = {Red value, Green value, Blue value};
    // You can use Google to find RGB values for your colors - https://www.google.com/search?q=color+picker
    uint8_t R[3] = {255,0,0};
    uint8_t G[3] = {0,255,0};
    uint8_t B[3] = {0,0,255};
    uint8_t W[3] = {255,255,255};
    uint8_t x[3] = {0,0,0}; //off aka black
    uint8_t R2[3] = {80,0,0};
    uint8_t R3[3] = {24,0,0};


    // Copy, Paste, and Edit this block of code below with your color 
    // variables to make your pixel art and animations. Make sure 
    // to increment 'ColorMap#' by one with each copy/paste. 
    // Ensure that the matrix dimensions match the 'NumberOfRows' 
    // and 'NumberOfColumns' defined at the beginning of this
    // program, and match in the functions parameters above.
    // This is memory inefficient so only a few of these can be 
    // supported, use it to easily change many pixels at once.

    // I use this matrix to turn off LEDs.
    // Start Copy here:
    uint8_t *ColorMap0[NumberOfRows][NumberOfColumns] = {
     //0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
      {x, x, x, x, x, x, x, x, x, x, x, x, x, x, x}, //0
      {x, x, x, x, x, x, x, x, x, x, x, x, x, x, x}, //1
      {x, x, x, x, x, x, x, x, x, x, x, x, x, x, x}, //2
      {x, x, x, x, x, x, x, x, x, x, x, x, x, x, x}, //3
      {x, x, x, x, x, x, x, x, x, x, x, x, x, x, x}, //4
      {x, x, x, x, x, x, x, x, x, x, x, x, x, x, x}, //5
      {x, x, x, x, x, x, x, x, x, x, x, x, x, x, x}, //6
      {x, x, x, x, x, x, x, x, x, x, x, x, x, x, x}, //7
      {x, x, x, x, x, x, x, x, x, x, x, x, x, x, x}, //8
      {x, x, x, x, x, x, x, x, x, x, x, x, x, x, x}, //9
    };
    // End Copy here.

    // The Miami University Logo in pixel form.
    uint8_t *ColorMap1[NumberOfRows][NumberOfColumns] = {
     //0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
      {x, W, W, W, W, W, x, x, x, W, W, W, W, W, x}, //0
      {x, W, x, R, R, x, W, x, W, x, R, R, x, W, x}, //1
      {x, x, W, x, R, R, x, W, x, R, R, x, W, x, x}, //2
      {x, x, W, x, R, R, R, x, R, R, R, x, W, x, x}, //3
      {x, x, W, x, R, x, R, R, R, x, R, x, W, x, x}, //4
      {x, x, W, x, R, x, x, R, x, x, R, x, W, x, x}, //5
      {x, x, W, x, R, x, W, x, W, x, R, x, W, x, x}, //6
      {x, W, x, R, R, R, x, W, x, R, R, R, x, W, x}, //7
      {x, W, W, W, W, W, W, W, W, W, W, W, W, W, x}, //8
      {x, x, x, x, x, x, x, x, x, x, x, x, x, x, x}, //9
    };


    // Copy, Paste, and Edit this block of code to turn on LEDs in
    // your defined order. Start with '1' and count up, use a number
    // more than once to turn on multiple LEDs at once. Skip a number
    // to wait longer before proceeding to the next LED to turn on.
    // Use '0' to not change a pixel. Make sure matrix dimensions are correct.
    // DON'T count higher than NUM_LEDS specified at the beginning of
    // the program. After defining the matrix of numbers, use the function 
    //    like this to light LEDs in a single color:
    // 'CustomDrawColor(Draw# matrix, color variable, delay time in ms);'
    //    Or, use the function like this to light LEDs based on a color matrix:
    // 'CustomDrawMatrix(Draw# matrix, ColorMap# matrix, delay time in ms);'

    // I use this matrix to create a spiral animation.
    // Start Copy here:
    uint8_t Draw0[NumberOfRows][NumberOfColumns] = {
     //  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
      {  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15}, //0
      { 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 16}, //1
      { 45, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 60, 17}, //2
      { 44, 83,114,115,116,117,118,119,120,121,122,123, 96, 61, 18}, //3
      { 43, 82,113,136,137,138,139,140,141,142,143,124, 97, 62, 19}, //4
      { 42, 81,112,135,150,149,148,147,146,145,144,125, 98, 63, 20}, //5
      { 41, 80,111,134,133,132,131,130,129,128,127,126, 99, 64, 21}, //6
      { 40, 79,110,109,108,107,106,105,104,103,102,101,100, 65, 22}, //7
      { 39, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 23}, //8
      { 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24}, //9
    };
    // End Copy here.


    // Now I begin with displaying my pixel art and animations.

    // Start the loop with the entire matrix off.
    LightEmUp(ColorMap0);
    delay(1000); //how long to stay here (ms)


    // Copy, Paste, and Edit this code below to change one
    // pixel at a time. Use it like this:
    // 'Change1LED(row location, column location, color variable);'

    // I use this to fill in the Red Pixels one at a time.
    // Start Copy here:
    Change1LED(7,3,R);
    delay(250); //how long to stay here (ms)
    // End Copy here.

    Change1LED(7,4,R);
    delay(250);
    
    Change1LED(7,5,R);
    Change1LED(6,4,R);
    delay(250);

    Change1LED(5,4,R);
    delay(250);

    // It's tedious and hard to visualize what's happening when
    // changing one pixel at a time, so I create a matrix
    // of numbers that show the counting order I want the LEDS displayed
    // picking up where I left off changing them LED by LED.
    // I skip numbers 20-26 to pause for a longer amount of time.
    uint8_t Draw1[NumberOfRows][NumberOfColumns] = {
     //0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
      {0,27,27,27,27,27, 0, 0, 0,27,27,27,27,27, 0}, //0
      {0,27, 0, 5, 4, 0,27, 0,27, 0,14,15, 0,27, 0}, //1
      {0, 0,27, 0, 3, 4, 0,27, 0,12,13, 0,27, 0, 0}, //2
      {0, 0,27, 0, 2, 5, 6, 0,10,11,14, 0,27, 0, 0}, //3
      {0, 0,27, 0, 1, 0, 7, 8, 9, 0,15, 0,27, 0, 0}, //4
      {0, 0,27, 0, 0, 0, 0, 9, 0, 0,16, 0,27, 0, 0}, //5
      {0, 0,27, 0, 0, 0,27, 0,27, 0,17, 0,27, 0, 0}, //6
      {0,27, 0, 0, 0, 0, 0,27, 0,19,18,19, 0,27, 0}, //7
      {0,27,27,27,27,27,27,27,27,27,27,27,27,27, 0}, //8
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //9
    };

    // I use the 'CustomDrawMatrix' function with my 'Draw1' and 'ColorMap1'
    // matrices to continue drawing the Miami Logo. I wait 250 milliseconds
    // before incrementing to the next value.
    CustomDrawMatrix(Draw1, ColorMap1, 250);
    delay(2750); // Wait 2.75s after finishing drawing the enitre matrix.

    // Now I blink the Miami University Logo on and off for a few seconds.
    LightEmUp(ColorMap0); // Turn the LEDs off.
    delay(1000);
    LightEmUp(ColorMap1); // Show the Logo again.
    delay(1000);
    LightEmUp(ColorMap0); // Turn the LEDs off.
    delay(1000);
    LightEmUp(ColorMap1); // Show the Logo again.
    delay(1000);

    // I turn all the LEDs to Red in a spiral fashion.
    CustomDrawColor(Draw0, R2, 10);
    // I do the same thing with a darker red.
    CustomDrawColor(Draw0, R3, 10);
    // I finish with the same spiral to black.
    CustomDrawColor(Draw0, x, 10);
    delay(3950); // Wait 3.95s before returning to the beginning of
    // void loop() and starting the whole process over.
}


