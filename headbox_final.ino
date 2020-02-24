// Adafruit_NeoMatrix example for single NeoPixel Shield.
// By Marc MERLIN <marc_soft@merlins.org>
// Contains code (c) Adafruit, license BSD

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

// Choose your prefered pixmap
//#include "heart24.h"
//#include "yellowsmiley24.h"
//#include "bluesmiley24.h"
//#include "smileytongue24.h"
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PIN 12
#define PIN2 11
#define PIN3 10
#define PIN4 9
#define LED_RING_PIN 2

#define LED_RING_COUNT 25

Adafruit_NeoPixel ring(LED_RING_COUNT, LED_RING_PIN, NEO_GRB + NEO_KHZ800);

// ESP8266 has an I2S neopixel library which can only use pin RX
// so it's recommended to use the same pin with Neopixel to avoid
// rewiring when changing libs
#ifdef ESP8266
#define PIN RX
#endif

// Max is 255, 32 is a conservative value to not overload
// a USB power supply (500mA) for 12x12 pixels.
#define BRIGHTNESS 50

// Define matrix width and height.
#define mw 16
#define mh 8

// MATRIX DECLARATION:
// Parameter 1 = width of EACH NEOPIXEL MATRIX (not total display)
// Parameter 2 = height of each matrix
// Parameter 3 = number of matrices arranged horizontally
// Parameter 4 = number of matrices arranged vertically
// Parameter 5 = pin number (most are valid)
// Parameter 6 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the FIRST MATRIX; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs WITHIN EACH MATRIX are
//     arranged in horizontal rows or in vertical columns, respectively;
//     pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns WITHIN
//     EACH MATRIX proceed in the same order, or alternate lines reverse
//     direction; pick one.
//   NEO_TILE_TOP, NEO_TILE_BOTTOM, NEO_TILE_LEFT, NEO_TILE_RIGHT:
//     Position of the FIRST MATRIX (tile) in the OVERALL DISPLAY; pick
//     two, e.g. NEO_TILE_TOP + NEO_TILE_LEFT for the top-left corner.
//   NEO_TILE_ROWS, NEO_TILE_COLUMNS: the matrices in the OVERALL DISPLAY
//     are arranged in horizontal rows or in vertical columns, respectively;
//     pick one or the other.
//   NEO_TILE_PROGRESSIVE, NEO_TILE_ZIGZAG: the ROWS/COLUMS OF MATRICES
//     (tiles) in the OVERALL DISPLAY proceed in the same order for every
//     line, or alternate lines reverse direction; pick one.  When using
//     zig-zag order, the orientation of the matrices in alternate rows
//     will be rotated 180 degrees (this is normal -- simplifies wiring).
//   See example below for these values in action.
// Parameter 7 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 pixels)
//   NEO_GRB     Pixels are wired for GRB bitstream (v2 pixels)
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA v1 pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)

Adafruit_NeoMatrix *matrix = new Adafruit_NeoMatrix(mw, mh, PIN,
    NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
    NEO_GRB            + NEO_KHZ800);

Adafruit_NeoMatrix *matrix2 = new Adafruit_NeoMatrix(mw, mh, PIN2,
    NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
    NEO_GRB            + NEO_KHZ800);

Adafruit_NeoMatrix *matrix3 = new Adafruit_NeoMatrix(mw, mh, PIN3,
    NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
    NEO_GRB            + NEO_KHZ800);

Adafruit_NeoMatrix *backwards_matrix = new Adafruit_NeoMatrix(mw, mh, PIN4,
    NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
    NEO_GRB            + NEO_KHZ800);

// This could also be defined as matrix->color(255,0,0) but those defines
// are meant to work for adafruit_gfx backends that are lacking color()
#define LED_BLACK		0

#define LED_RED_VERYLOW 	(3 <<  11)
#define LED_RED_LOW 		(7 <<  11)
#define LED_RED_MEDIUM 		(15 << 11)
#define LED_RED_HIGH 		(31 << 11)

#define LED_GREEN_VERYLOW	(1 <<  5)
#define LED_GREEN_LOW 		(15 << 5)
#define LED_GREEN_MEDIUM 	(31 << 5)
#define LED_GREEN_HIGH 		(63 << 5)

#define LED_BLUE_VERYLOW	3
#define LED_BLUE_LOW 		7
#define LED_BLUE_MEDIUM 	15
#define LED_BLUE_HIGH 		31

#define LED_ORANGE_VERYLOW	(LED_RED_VERYLOW + LED_GREEN_VERYLOW)
#define LED_ORANGE_LOW		(LED_RED_LOW     + LED_GREEN_LOW)
#define LED_ORANGE_MEDIUM	(LED_RED_MEDIUM  + LED_GREEN_MEDIUM)
#define LED_ORANGE_HIGH		(LED_RED_HIGH    + LED_GREEN_HIGH)

#define LED_PURPLE_VERYLOW	(LED_RED_VERYLOW + LED_BLUE_VERYLOW)
#define LED_PURPLE_LOW		(LED_RED_LOW     + LED_BLUE_LOW)
#define LED_PURPLE_MEDIUM	(LED_RED_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_PURPLE_HIGH		(LED_RED_HIGH    + LED_BLUE_HIGH)

#define LED_CYAN_VERYLOW	(LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_CYAN_LOW		(LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_CYAN_MEDIUM		(LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_CYAN_HIGH		(LED_GREEN_HIGH    + LED_BLUE_HIGH)

#define LED_WHITE_VERYLOW	(LED_RED_VERYLOW + LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_WHITE_LOW		(LED_RED_LOW     + LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_WHITE_MEDIUM	(LED_RED_MEDIUM  + LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_WHITE_HIGH		(LED_RED_HIGH    + LED_GREEN_HIGH    + LED_BLUE_HIGH)

static const uint8_t PROGMEM
mono_bmp[][8] =
{
  { // 0: checkered 1
    B10101010,
    B01010101,
    B10101010,
    B01010101,
    B10101010,
    B01010101,
    B10101010,
    B01010101,
  },

  { // 1: checkered 2
    B01010101,
    B10101010,
    B01010101,
    B10101010,
    B01010101,
    B10101010,
    B01010101,
    B10101010,
  },

  { // 2: smiley
    B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100
  },

  { // 3: neutral
    B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10111101,
    B10000001,
    B01000010,
    B00111100
  },

  { // 4; frowny
    B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100
  },
};

static const uint16_t PROGMEM
// These bitmaps were written for a backend that only supported
// 4 bits per color with Blue/Green/Red ordering while neomatrix
// uses native 565 color mapping as RGB.
// I'm leaving the arrays as is because it's easier to read
// which color is what when separated on a 4bit boundary
// The demo code will modify the arrays at runtime to be compatible
// with the neomatrix color ordering and bit depth.
RGB_bmp[][64] = {
  // 00: blue, blue/red, red, red/green, green, green/blue, blue, white
  { 0x100, 0x200, 0x300, 0x400, 0x600, 0x800, 0xA00, 0xF00,
    0x101, 0x202, 0x303, 0x404, 0x606, 0x808, 0xA0A, 0xF0F,
    0x001, 0x002, 0x003, 0x004, 0x006, 0x008, 0x00A, 0x00F,
    0x011, 0x022, 0x033, 0x044, 0x066, 0x088, 0x0AA, 0x0FF,
    0x010, 0x020, 0x030, 0x040, 0x060, 0x080, 0x0A0, 0x0F0,
    0x110, 0x220, 0x330, 0x440, 0x660, 0x880, 0xAA0, 0xFF0,
    0x100, 0x200, 0x300, 0x400, 0x600, 0x800, 0xA00, 0xF00,
    0x111, 0x222, 0x333, 0x444, 0x666, 0x888, 0xAAA, 0xFFF,
  },

  // 01: grey to white
  { 0x111, 0x222, 0x333, 0x555, 0x777, 0x999, 0xAAA, 0xFFF,
    0x222, 0x222, 0x333, 0x555, 0x777, 0x999, 0xAAA, 0xFFF,
    0x333, 0x333, 0x333, 0x555, 0x777, 0x999, 0xAAA, 0xFFF,
    0x555, 0x555, 0x555, 0x555, 0x777, 0x999, 0xAAA, 0xFFF,
    0x777, 0x777, 0x777, 0x777, 0x777, 0x999, 0xAAA, 0xFFF,
    0x999, 0x999, 0x999, 0x999, 0x999, 0x999, 0xAAA, 0xFFF,
    0xAAA, 0xAAA, 0xAAA, 0xAAA, 0xAAA, 0xAAA, 0xAAA, 0xFFF,
    0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF,
  },

  // 02: low red to high red
  { 0x001, 0x002, 0x003, 0x005, 0x007, 0x009, 0x00A, 0x00F,
    0x002, 0x002, 0x003, 0x005, 0x007, 0x009, 0x00A, 0x00F,
    0x003, 0x003, 0x003, 0x005, 0x007, 0x009, 0x00A, 0x00F,
    0x005, 0x005, 0x005, 0x005, 0x007, 0x009, 0x00A, 0x00F,
    0x007, 0x007, 0x007, 0x007, 0x007, 0x009, 0x00A, 0x00F,
    0x009, 0x009, 0x009, 0x009, 0x009, 0x009, 0x00A, 0x00F,
    0x00A, 0x00A, 0x00A, 0x00A, 0x00A, 0x00A, 0x00A, 0x00F,
    0x00F, 0x00F, 0x00F, 0x00F, 0x00F, 0x00F, 0x00F, 0x00F,
  },

  // 03: low green to high green
  { 0x010, 0x020, 0x030, 0x050, 0x070, 0x090, 0x0A0, 0x0F0,
    0x020, 0x020, 0x030, 0x050, 0x070, 0x090, 0x0A0, 0x0F0,
    0x030, 0x030, 0x030, 0x050, 0x070, 0x090, 0x0A0, 0x0F0,
    0x050, 0x050, 0x050, 0x050, 0x070, 0x090, 0x0A0, 0x0F0,
    0x070, 0x070, 0x070, 0x070, 0x070, 0x090, 0x0A0, 0x0F0,
    0x090, 0x090, 0x090, 0x090, 0x090, 0x090, 0x0A0, 0x0F0,
    0x0A0, 0x0A0, 0x0A0, 0x0A0, 0x0A0, 0x0A0, 0x0A0, 0x0F0,
    0x0F0, 0x0F0, 0x0F0, 0x0F0, 0x0F0, 0x0F0, 0x0F0, 0x0F0,
  },

  // 04: low blue to high blue
  { 0x100, 0x200, 0x300, 0x500, 0x700, 0x900, 0xA00, 0xF00,
    0x200, 0x200, 0x300, 0x500, 0x700, 0x900, 0xA00, 0xF00,
    0x300, 0x300, 0x300, 0x500, 0x700, 0x900, 0xA00, 0xF00,
    0x500, 0x500, 0x500, 0x500, 0x700, 0x900, 0xA00, 0xF00,
    0x700, 0x700, 0x700, 0x700, 0x700, 0x900, 0xA00, 0xF00,
    0x900, 0x900, 0x900, 0x900, 0x900, 0x900, 0xA00, 0xF00,
    0xA00, 0xA00, 0xA00, 0xA00, 0xA00, 0xA00, 0xA00, 0xF00,
    0xF00, 0xF00, 0xF00, 0xF00, 0xF00, 0xF00, 0xF00, 0xF00,
  },

  // 05: 1 black, 2R, 2O, 2G, 1B with 4 blue lines rising right
  { 0x000, 0x200, 0x000, 0x400, 0x000, 0x800, 0x000, 0xF00,
    0x000, 0x201, 0x002, 0x403, 0x004, 0x805, 0x006, 0xF07,
    0x008, 0x209, 0x00A, 0x40B, 0x00C, 0x80D, 0x00E, 0xF0F,
    0x000, 0x211, 0x022, 0x433, 0x044, 0x855, 0x066, 0xF77,
    0x088, 0x299, 0x0AA, 0x4BB, 0x0CC, 0x8DD, 0x0EE, 0xFFF,
    0x000, 0x210, 0x020, 0x430, 0x040, 0x850, 0x060, 0xF70,
    0x080, 0x290, 0x0A0, 0x4B0, 0x0C0, 0x8D0, 0x0E0, 0xFF0,
    0x000, 0x200, 0x000, 0x500, 0x000, 0x800, 0x000, 0xF00,
  },

  // 06: 4 lines of increasing red and then green
  { 0x000, 0x000, 0x001, 0x001, 0x002, 0x002, 0x003, 0x003,
    0x004, 0x004, 0x005, 0x005, 0x006, 0x006, 0x007, 0x007,
    0x008, 0x008, 0x009, 0x009, 0x00A, 0x00A, 0x00B, 0x00B,
    0x00C, 0x00C, 0x00D, 0x00D, 0x00E, 0x00E, 0x00F, 0x00F,
    0x000, 0x000, 0x010, 0x010, 0x020, 0x020, 0x030, 0x030,
    0x040, 0x040, 0x050, 0x050, 0x060, 0x060, 0x070, 0x070,
    0x080, 0x080, 0x090, 0x090, 0x0A0, 0x0A0, 0x0B0, 0x0B0,
    0x0C0, 0x0C0, 0x0D0, 0x0D0, 0x0E0, 0x0E0, 0x0F0, 0x0F0,
  },

  // 07: 4 lines of increasing red and then blue
  { 0x000, 0x000, 0x001, 0x001, 0x002, 0x002, 0x003, 0x003,
    0x004, 0x004, 0x005, 0x005, 0x006, 0x006, 0x007, 0x007,
    0x008, 0x008, 0x009, 0x009, 0x00A, 0x00A, 0x00B, 0x00B,
    0x00C, 0x00C, 0x00D, 0x00D, 0x00E, 0x00E, 0x00F, 0x00F,
    0x000, 0x000, 0x100, 0x100, 0x200, 0x200, 0x300, 0x300,
    0x400, 0x400, 0x500, 0x500, 0x600, 0x600, 0x700, 0x700,
    0x800, 0x800, 0x900, 0x900, 0xA00, 0xA00, 0xB00, 0xB00,
    0xC00, 0xC00, 0xD00, 0xD00, 0xE00, 0xE00, 0xF00, 0xF00,
  },

  // 08: criss cross of green and red with diagonal blue.
  { 0xF00, 0x001, 0x003, 0x005, 0x007, 0x00A, 0x00F, 0x000,
    0x020, 0xF21, 0x023, 0x025, 0x027, 0x02A, 0x02F, 0x020,
    0x040, 0x041, 0xF43, 0x045, 0x047, 0x04A, 0x04F, 0x040,
    0x060, 0x061, 0x063, 0xF65, 0x067, 0x06A, 0x06F, 0x060,
    0x080, 0x081, 0x083, 0x085, 0xF87, 0x08A, 0x08F, 0x080,
    0x0A0, 0x0A1, 0x0A3, 0x0A5, 0x0A7, 0xFAA, 0x0AF, 0x0A0,
    0x0F0, 0x0F1, 0x0F3, 0x0F5, 0x0F7, 0x0FA, 0xFFF, 0x0F0,
    0x000, 0x001, 0x003, 0x005, 0x007, 0x00A, 0x00F, 0xF00,
  },

  // 09: 2 lines of green, 2 red, 2 orange, 2 green
  { 0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0,
    0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0,
    0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0,
    0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0,
    0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0,
    0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0,
    0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0,
    0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0,
  },

  // 10: multicolor smiley face
  { 0x000, 0x000, 0x00F, 0x00F, 0x00F, 0x00F, 0x000, 0x000,
    0x000, 0x00F, 0x000, 0x000, 0x000, 0x000, 0x00F, 0x000,
    0x00F, 0x000, 0xF00, 0x000, 0x000, 0xF00, 0x000, 0x00F,
    0x00F, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x00F,
    0x00F, 0x000, 0x0F0, 0x000, 0x000, 0x0F0, 0x000, 0x00F,
    0x00F, 0x000, 0x000, 0x0F4, 0x0F3, 0x000, 0x000, 0x00F,
    0x000, 0x00F, 0x000, 0x000, 0x000, 0x000, 0x00F, 0x000,
    0x000, 0x000, 0x00F, 0x00F, 0x00F, 0x00F, 0x000, 0x000,
  },
};


// Convert a BGR 4/4/4 bitmap to RGB 5/6/5 used by Adafruit_GFX
void fixdrawRGBBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h) {
  uint16_t RGB_bmp_fixed[w * h];
  for (uint16_t pixel = 0; pixel < w * h; pixel++) {
    uint8_t r, g, b;
    uint16_t color = pgm_read_word(bitmap + pixel);

    //Serial.print(color, HEX);
    b = (color & 0xF00) >> 8;
    g = (color & 0x0F0) >> 4;
    r = color & 0x00F;
    //Serial.print(" ");
    //Serial.print(b);
    //Serial.print("/");
    //Serial.print(g);
    //Serial.print("/");
    //Serial.print(r);
    //Serial.print(" -> ");
    // expand from 4/4/4 bits per color to 5/6/5
    b = map(b, 0, 15, 0, 31);
    g = map(g, 0, 15, 0, 63);
    r = map(r, 0, 15, 0, 31);
    //Serial.print(r);
    //Serial.print("/");
    //Serial.print(g);
    //Serial.print("/");
    //Serial.print(b);
    RGB_bmp_fixed[pixel] = (r << 11) + (g << 5) + b;
    //Serial.print(" -> ");
    //Serial.println(RGB_bmp_fixed[pixel], HEX);
  }
  matrix->drawRGBBitmap(x, y, RGB_bmp_fixed, w, h);
}



void display_microsoft() {
  matrix->clear();
  matrix2->clear();
  matrix3->clear();
  backwards_matrix->clear();
  matrix->fillRect(0, 0, 8, 4, LED_RED_HIGH);
  matrix->fillRect(8, 0, 8, 4, LED_GREEN_HIGH);
  matrix->fillRect(0, 4, 8, 4, LED_BLUE_HIGH);
  matrix->fillRect(8, 4, 8, 4, LED_ORANGE_HIGH);

  matrix2->fillRect(0, 0, 8, 4, LED_RED_HIGH);
  matrix2->fillRect(8, 0, 8, 4, LED_GREEN_HIGH);
  matrix2->fillRect(0, 4, 8, 4, LED_BLUE_HIGH);
  matrix2->fillRect(8, 4, 8, 4, LED_ORANGE_HIGH);

  matrix3->fillRect(0, 0, 8, 4, LED_RED_HIGH);
  matrix3->fillRect(8, 0, 8, 4, LED_GREEN_HIGH);
  matrix3->fillRect(0, 4, 8, 4, LED_BLUE_HIGH);
  matrix3->fillRect(8, 4, 8, 4, LED_ORANGE_HIGH);

  backwards_matrix->fillRect(0, 0, 8, 4, LED_RED_HIGH);
  backwards_matrix->fillRect(8, 0, 8, 4, LED_GREEN_HIGH);
  backwards_matrix->fillRect(0, 4, 8, 4, LED_BLUE_HIGH);
  backwards_matrix->fillRect(8, 4, 8, 4, LED_ORANGE_HIGH);

  matrix->show();
  matrix2->show();
  matrix3->show();
  backwards_matrix->show();

}

void display_mc() {
  matrix->clear();
  matrix2->clear();
  matrix3->clear();
  backwards_matrix->clear();

  matrix->fillRect(0, 0, mw, mh, LED_WHITE_MEDIUM);
  matrix->fillCircle(6, mh / 2, 2, LED_RED_HIGH);
  matrix->fillCircle(10, mh / 2, 2, LED_ORANGE_HIGH);

  matrix2->fillRect(0, 0, mw, mh, LED_WHITE_MEDIUM);
  matrix2->fillCircle(6, mh / 2, 2, LED_RED_HIGH);
  matrix2->fillCircle(10, mh / 2, 2, LED_ORANGE_HIGH);

  matrix3->fillRect(0, 0, mw, mh, LED_WHITE_MEDIUM);
  matrix3->fillCircle(6, mh / 2, 2, LED_RED_HIGH);
  matrix3->fillCircle(10, mh / 2, 2, LED_ORANGE_HIGH);

  backwards_matrix->fillRect(0, 0, mw, mh, LED_WHITE_MEDIUM);
  backwards_matrix->fillCircle(6, mh / 2, 2, LED_RED_HIGH);
  backwards_matrix->fillCircle(10, mh / 2, 2, LED_ORANGE_HIGH);

  matrix->show();
  matrix2->show();
  matrix3->show();
  backwards_matrix->show();
}






void display_target() {
  matrix->clear();
  matrix2->clear();
  matrix3->clear();
  backwards_matrix->clear();

  matrix->fillRect(0, 0, mw, mh, LED_RED_HIGH);
  matrix->drawCircle(mw / 2, mh / 2, 6, LED_WHITE_MEDIUM);
  matrix->fillCircle(mw / 2, mh / 2, 3, LED_WHITE_MEDIUM);

  matrix2->fillRect(0, 0, mw, mh, LED_RED_HIGH);
  matrix2->drawCircle(mw / 2, mh / 2, 6, LED_WHITE_MEDIUM);
  matrix2->fillCircle(mw / 2, mh / 2, 3, LED_WHITE_MEDIUM);

  matrix3->fillRect(0, 0, mw, mh, LED_RED_HIGH);
  matrix3->drawCircle(mw / 2, mh / 2, 6, LED_WHITE_MEDIUM);
  matrix3->fillCircle(mw / 2, mh / 2, 3, LED_WHITE_MEDIUM);

  backwards_matrix->fillRect(0, 0, mw, mh, LED_RED_HIGH);
  backwards_matrix->drawCircle(mw / 2, mh / 2, 6, LED_WHITE_MEDIUM);
  backwards_matrix->fillCircle(mw / 2, mh / 2, 3, LED_WHITE_MEDIUM);

  matrix->show();
  matrix2->show();
  matrix3->show();
  backwards_matrix->show();
}


void display_scrollM() {
  matrix->clear();
  matrix2->clear();
  matrix3->clear();
  backwards_matrix->clear();

  matrix->setTextWrap(false);  // we don't wrap text so it scrolls nicely
  matrix->setTextSize(1);
  matrix->setRotation(0);

  matrix2->setTextWrap(false);  // we don't wrap text so it scrolls nicely
  matrix2->setTextSize(1);
  matrix2->setRotation(0);

  matrix3->setTextWrap(false);  // we don't wrap text so it scrolls nicely
  matrix3->setTextSize(1);
  matrix3->setRotation(0);

  backwards_matrix->setTextWrap(false);  // we don't wrap text so it scrolls nicely
  backwards_matrix->setTextSize(1);
  backwards_matrix->setRotation(0);

  for (int8_t x = -38; x <= 16; x++) {
    matrix->clear();
    matrix2->clear();
    matrix3->clear();
    backwards_matrix->clear();

    matrix->setCursor(x, 1);
    matrix2->setCursor(x, 1);
    matrix3->setCursor(x, 1);
    backwards_matrix->setCursor(x, 1);

    matrix->fillRect(0, 0, mw, mh, LED_RED_HIGH);
    matrix->setTextColor(LED_ORANGE_HIGH);
    matrix->print("M");

    matrix2->fillRect(0, 0, mw, mh, LED_RED_HIGH);
    matrix2->setTextColor(LED_ORANGE_HIGH);
    matrix2->print("M");

    matrix3->fillRect(0, 0, mw, mh, LED_RED_HIGH);
    matrix3->setTextColor(LED_ORANGE_HIGH);
    matrix3->print("M");

    backwards_matrix->fillRect(0, 0, mw, mh, LED_RED_HIGH);
    backwards_matrix->setTextColor(LED_ORANGE_HIGH);
    backwards_matrix->print("M");

    matrix->show();
    matrix2->show();
    matrix3->show();
    backwards_matrix->show();
    delay(50);
  }
}

void display_scrollf() {
  matrix->clear();
  matrix2->clear();
  matrix3->clear();
  backwards_matrix->clear();

  matrix->setTextWrap(false);  // we don't wrap text so it scrolls nicely
  matrix->setTextSize(1);
  matrix->setRotation(0);

  matrix2->setTextWrap(false);  // we don't wrap text so it scrolls nicely
  matrix2->setTextSize(1);
  matrix2->setRotation(0);

  matrix3->setTextWrap(false);  // we don't wrap text so it scrolls nicely
  matrix3->setTextSize(1);
  matrix3->setRotation(0);

  backwards_matrix->setTextWrap(false);  // we don't wrap text so it scrolls nicely
  backwards_matrix->setTextSize(1);
  backwards_matrix->setRotation(0);
  for (int8_t x = -38; x <= 16; x++) {
    matrix->clear();
    matrix2->clear();
    matrix3->clear();
    backwards_matrix->clear();

    matrix->setCursor(x, 1);
    matrix2->setCursor(x, 1);
    matrix3->setCursor(x, 1);
    backwards_matrix->setCursor(x, 1);

    matrix->fillRect(0, 0, mw, mh, LED_BLUE_HIGH);
    matrix->setTextColor(LED_WHITE_HIGH);
    matrix->print("f");

    matrix2->fillRect(0, 0, mw, mh, LED_BLUE_HIGH);
    matrix2->setTextColor(LED_WHITE_HIGH);
    matrix2->print("f");

    matrix3->fillRect(0, 0, mw, mh, LED_BLUE_HIGH);
    matrix3->setTextColor(LED_WHITE_HIGH);
    matrix3->print("f");

    backwards_matrix->fillRect(0, 0, mw, mh, LED_BLUE_HIGH);
    backwards_matrix->setTextColor(LED_WHITE_HIGH);
    backwards_matrix->print("f");

    matrix->show();
    matrix2->show();
    matrix3->show();
    backwards_matrix->show();
    delay(50);
  }
}

void display_scrolla() {
  matrix->clear();
  matrix2->clear();
  matrix3->clear();
  backwards_matrix->clear();

  matrix->setTextWrap(false);  // we don't wrap text so it scrolls nicely
  matrix->setTextSize(1);
  matrix->setRotation(0);

  matrix2->setTextWrap(false);  // we don't wrap text so it scrolls nicely
  matrix2->setTextSize(1);
  matrix2->setRotation(0);

  matrix3->setTextWrap(false);  // we don't wrap text so it scrolls nicely
  matrix3->setTextSize(1);
  matrix3->setRotation(0);

  backwards_matrix->setTextWrap(false);  // we don't wrap text so it scrolls nicely
  backwards_matrix->setTextSize(1);
  backwards_matrix->setRotation(0);

  for (int8_t x = -38; x <= 16; x++) {
    matrix->clear();
    matrix2->clear();
    matrix3->clear();
    backwards_matrix->clear();

    matrix->setCursor(x, 1);
    matrix2->setCursor(x, 1);
    matrix3->setCursor(x, 1);
    backwards_matrix->setCursor(x, 1);

    matrix->fillRect(0, 0, mw, mh, LED_WHITE_MEDIUM);
    matrix->setTextColor(LED_BLACK);
    matrix->print("a");

    matrix2->fillRect(0, 0, mw, mh, LED_WHITE_MEDIUM);
    matrix2->setTextColor(LED_BLACK);
    matrix2->print("a");

    matrix3->fillRect(0, 0, mw, mh, LED_WHITE_MEDIUM);
    matrix3->setTextColor(LED_BLACK);
    matrix3->print("a");

    backwards_matrix->fillRect(0, 0, mw, mh, LED_WHITE_MEDIUM);
    backwards_matrix->setTextColor(LED_BLACK);
    backwards_matrix->print("a");

    matrix->show();
    matrix2->show();
    matrix3->show();
    backwards_matrix->show();
    delay(50);
  }
}

void ringWipe(int32_t color, int wait){
  for (int i = 0; i < ring.numPixels(); i++){
    ring.setPixelColor(i,color);
    ring.show();
  }
  
}






void loop() {
  // clear the screen after X bitmaps have been displayed and we
  // loop back to the top left corner
  // 8x8 => 1, 16x8 => 2, 17x9 => 6

  ringWipe(ring.Color(255, 153, 18),40);
  
  static uint8_t pixmap_count = ((mw + 7) / 8) * ((mh + 7) / 8);


  display_microsoft();
  delay(2000);
  //display_target();
  display_mc();
  matrix->clear();
  matrix2->clear();
  matrix3->clear();
  backwards_matrix->clear();
  delay(3000);

  display_scrollM();
  delay(2000);
  display_scrollf();
  delay(2000);
  //display_scrolla();
  matrix->clear();
  matrix2->clear();
  matrix3->clear();
  backwards_matrix->clear();
  delay(2000);

}

void setup() {
  Serial.begin(115200);

  ring.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  ring.show();            // Turn OFF all pixels ASAP
  ring.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  
  matrix->begin();
  matrix2->begin();
  matrix3->begin();
  backwards_matrix->begin();
  
  matrix->setTextWrap(false);
  matrix2->setTextWrap(false);
  matrix3->setTextWrap(false);
  backwards_matrix->setTextWrap(false);
  
  matrix->setBrightness(BRIGHTNESS);
  matrix2->setBrightness(BRIGHTNESS);
  matrix3->setBrightness(BRIGHTNESS);
  backwards_matrix->setBrightness(BRIGHTNESS);
  
  matrix->show();
  matrix2->show();
  matrix3->show();
  backwards_matrix->show();
  delay(1000);
  matrix->clear();
  matrix2->clear();
  matrix3->clear();
  backwards_matrix->clear();
}

// vim:sts=4:sw=4
