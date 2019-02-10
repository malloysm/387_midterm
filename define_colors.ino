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

void setup() {
  delay( 3000 );
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness( BRIGHTNESS );
}

//     XY(x,y) takes x and y coordinates and returns an LED index number,
//             for use like this:  leds[ XY(x,y) ] == CRGB::Red;


// Params for width and height
const uint8_t kMatrixWidth = 15;
const uint8_t kMatrixHeight = 10;

uint8_t *ColorMap[kMatrixWidth][kMatrixHeight];

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
// Use the "XY" function like this:
//
//    for( uint8_t x = 0; x < kMatrixWidth; x++) {
//      for( uint8_t y = 0; y < kMatrixHeight; y++) {
//      
//        // Here's the x, y to 'led index' in action: 
//        leds[ XY( x, y) ] = CHSV( random8(), 255, 255);
//      
//      }
//    }
//

// This takes the x,y coordinates and generates the
// corresponding LED pixel based on the matrix setup.
uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  
  if( kMatrixSerpentineLayout == false) {
    i = (y * kMatrixWidth) + x;
  }

  if( kMatrixSerpentineLayout == true) {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  }
  
  return i;
}

// Demo that USES "XY" follows code below

void loop()
{
    ColorMap[0][0] = R;
    leds[ XY( 0, 0) ] = CRGB(*(ColorMap[0][0]),*((ColorMap[0][0])+1),*((ColorMap[0][0])+2));
    ColorMap[1][0] = G;
    leds[ XY( 1, 0) ] = CRGB(*(ColorMap[1][0]),*((ColorMap[1][0])+1),*((ColorMap[1][0])+2));
    ColorMap[2][0] = B;
    leds[ XY( 2, 0) ] = CRGB(*(ColorMap[2][0]),*((ColorMap[2][0])+1),*((ColorMap[2][0])+2));
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.show();
}


