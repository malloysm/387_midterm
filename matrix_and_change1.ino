#include <FastLED.h>

#define LED_PIN  3

#define COLOR_ORDER GRB
#define CHIPSET     WS2812B
#define NUM_LEDS    150
CRGB leds[NUM_LEDS];

#define BRIGHTNESS 32

// Create and Edit color definitions here
uint8_t R[3] = {255,0,0};
uint8_t G[3] = {0,255,0};
uint8_t B[3] = {0,0,255};
uint8_t W[3] = {255,255,255};
uint8_t x[3] = {0,0,0}; //off aka black

void setup() {
  delay( 3000 );
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(BRIGHTNESS);
}

//     XY(x,y) takes x and y coordinates and returns an LED index number,
//             for use like this:  leds[ XY(x,y) ] == CRGB::Red;


// Params for width and height
const uint8_t NumberOfColumns = 15;
const uint8_t NumberOfRows = 10;

uint8_t *ColorMap[NumberOfRows][NumberOfColumns];

// Param for different pixel layouts
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
//                         |
//     .----<----<----<----'
//     |
//    15 > 16 > 17 > 18 > 19
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

// This function will return the right 'led index number' for 
// a given set of X and Y coordinates on your matrix.  
//

// This takes the x,y coordinates and generates the
// corresponding LED pixel based on the matrix setup.
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
  i = i%NUM_LEDS; // If more LEDS assigned than defined, this wraps them back to the front
  return i;
}

// Demo that USES "XY" follows code below

void loop()
{
    // Copy, Paste, and Edit this block of code with your color 
    // variables to make your pixel art and animations. Make sure 
    // to increment 'ColorMap#' by one with each copy/paste. 
    // Ensure that the matrix dimensions match the 'NumberOfRows' 
    // and 'NumberOfColumns' defined at the beginning of this
    // program, and match in the 'LightEmUp' function parameters.
    // This is memory inefficient so only a few of these can be 
    // supported, use it to easily change many pixels at once.

    // Start Copy here:
    uint8_t *ColorMap1[NumberOfRows][NumberOfColumns] = {
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
      {G, G, G, G, G, G, G, G, G, G, G, G, G, G, G}, //9
    };
    LightEmUp(ColorMap1);
    delay(200); //how long to stay here (ms)
    // End Copy here.


    // Copy, Paste, and Edit this code below to change one
    // pixel at a time. 'Change1LED(row,column,color)'

    // Start Copy here:
    Change1LED(7,3,R);
    delay(200); //how long to stay here (ms)
    // End Copy here.

    Change1LED(7,4,R);
    delay(200); //how long to stay here (ms)
    
    Change1LED(7,5,R);
    Change1LED(6,4,R);
    delay(200); //how long to stay here (ms)

    Change1LED(5,4,R);
    delay(200); //how long to stay here (ms)

    Change1LED(4,4,R);
    delay(200); //how long to stay here (ms)

    Change1LED(3,4,R);
    delay(200); //how long to stay here (ms)

    Change1LED(2,4,R);
    delay(200); //how long to stay here (ms)

    Change1LED(1,4,R);
    Change1LED(2,5,R);
    delay(200); //how long to stay here (ms)

    Change1LED(1,3,R);
    Change1LED(3,5,R);
    delay(200); //how long to stay here (ms)

    Change1LED(3,6,R);
    delay(200); //how long to stay here (ms)

    Change1LED(4,6,R);
    delay(200); //how long to stay here (ms)

    Change1LED(4,7,R);
    delay(200); //how long to stay here (ms)

    Change1LED(5,7,R);
    Change1LED(4,8,R);
    delay(200); //how long to stay here (ms)

    Change1LED(3,8,R);
    delay(200); //how long to stay here (ms)

    Change1LED(3,9,R);
    delay(200); //how long to stay here (ms)

    Change1LED(2,9,R);
    delay(200); //how long to stay here (ms)

    Change1LED(2,10,R);
    delay(200); //how long to stay here (ms)

    Change1LED(1,10,R);
    Change1LED(3,10,R);
    delay(200); //how long to stay here (ms)

    Change1LED(1,11,R);
    Change1LED(4,10,R);
    delay(200); //how long to stay here (ms)

    Change1LED(5,10,R);
    delay(200); //how long to stay here (ms)

    Change1LED(6,10,R);
    delay(200); //how long to stay here (ms)

    Change1LED(7,10,R);
    delay(200); //how long to stay here (ms)

    Change1LED(7,9,R);
    Change1LED(7,11,R);
    delay(200); //how long to stay here (ms)
    
    uint8_t *ColorMap0[NumberOfRows][NumberOfColumns] = {
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
      {G, G, G, G, G, G, G, G, G, G, G, G, G, G, G}, //9
    };
    LightEmUp(ColorMap0);
    delay(10000); //how long to stay here (ms)
}

// The 'LightEmUp' function uses the ColorMap to assign the user
// defined colors to the corresponding pixel.
// Once assigned the LEDS are all turned on at once.
// Edit number of columns here ----\/ also
void LightEmUp(uint8_t *ColorMap[][15])
{
  for(uint8_t column = 0; column < NumberOfColumns; column++) {
    for(uint8_t row = 0; row < NumberOfRows; row++) {
      leds[XY(row, column)] = CRGB(*(ColorMap[row][column]),*((ColorMap[row][column])+1),*((ColorMap[row][column])+2));  
      }
    }
  FastLED.show();
}

// The 'Change1LED' function will assign the specified color to the
// LED at the index provided and then show it.
void Change1LED(uint8_t row, uint8_t column, uint8_t *color)
{
  leds[XY(row, column)] = CRGB(*color,*(color+1),*(color+2));
  FastLED.show();
}


