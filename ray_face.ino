#include <FastLED_NeoMatrix.h>

#include <FastLED.h>

#include "config.h"

#define NUM_LEDS 64
#define LED_PIN 13
#define LED_TYPE WS2812
#define FASTLED_INTERNAL
#define COLOR_ORDER  GRB

int incomingByte;
CRGB leds[NUMMATRIX] = {0};

FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(
    leds, MATRIX_TILE_WIDTH,MATRIX_TILE_HEIGHT,1,1,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE
    );

const uint16_t colors[] = {
  matrix->Color(255, 0, 0), matrix->Color(0, 255, 0), matrix->Color(0, 0, 255) };

const uint16_t blue = matrix->Color(0,0,255);
const uint16_t clear = matrix->Color(0,0,0);
const uint16_t COLOR = blue;

void matrix_clear(){
  memset(leds, 0, NUMMATRIX*3);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  matrix->begin();
  matrix->setBrightness(brightness);
  matrix->setTextWrap(false);
  matrix->setTextColor(colors[0]);
  Serial.begin(9600);
}

int x    = mw;
int pass = 0;

void loop() {
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    if(incomingByte == 'h'){
      makeHappy();
    }
    if(incomingByte == 's'){
      makeSad();
    }
    if(incomingByte == 'b'){
      makeBlink();
    }
    if(incomingByte == 'd'){
      makeOwO1();
    }
  }
}


void makeHappy(){
  matrix->clear();
  matrix->drawLine(1,0,1,3,COLOR);
  matrix->drawLine(6,0,6,3,COLOR);
  matrix->drawPixel(1,6,COLOR);
  matrix->drawPixel(6,6,COLOR);
  matrix->drawLine(1,7,6,7,COLOR);
  matrix->show();
}

void makeSad(){
  matrix->clear();
  matrix->drawFastVLine(1,0,4,COLOR);
  matrix->drawFastVLine(6,0,4,COLOR);
  matrix->drawPixel(1,7,COLOR);
  matrix->drawPixel(6,7,COLOR);
  matrix->drawFastHLine(1,6,6,COLOR);
  matrix->show();
}

void makeMouth(){
  matrix->drawPixel(1,6,COLOR);
  matrix->drawPixel(2,7,COLOR);
  matrix->drawPixel(3,6,COLOR);
  matrix->drawPixel(4,7,COLOR);
  matrix->drawPixel(5,6,COLOR);
}

void makeOwO1(){
  matrix->clear();
  matrix->drawRoundRect(0,0,3,4,1,COLOR);
  matrix->drawRoundRect(5,0,3,4,1,COLOR);
  makeMouth();
  matrix->show();
}

void makeOwO2(){
  makeOwO1();
  matrix->drawPixel(1,0,clear);
  matrix->drawPixel(6,0,clear);
  matrix->show();
}

void makeOwO3(){
  matrix->clear();
  makeMouth();
  matrix->drawFastHLine(0,2,3,COLOR);
  matrix->drawFastHLine(5,2,3,COLOR);
  matrix->drawPixel(1,3,COLOR);
  matrix->drawPixel(6,3,COLOR);
  matrix->show();
}

void makeBlink(){
  matrix->clear();
  makeOwO1();
  delay(250);
  makeOwO2();
  delay(250);
  makeOwO3();
  delay(250);
  makeOwO2();
  delay(250);
  makeOwO1();
}