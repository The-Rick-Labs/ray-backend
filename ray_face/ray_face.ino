#include <FastLED_NeoMatrix.h>

#include <FastLED.h>

#include "config.h"

#define NUM_LEDS 64
#define LED_PIN 13
#define LED_TYPE WS2812
#define FASTLED_INTERNAL
#define COLOR_ORDER  GRB

int incomingByte;
int prevByte;
char mouth;

CRGB leds[NUMMATRIX] = {0};

FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(
    leds, MATRIX_TILE_WIDTH,MATRIX_TILE_HEIGHT,1,1,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE
    );

const uint16_t colors[] = {
  matrix->Color(255, 0, 0), matrix->Color(0, 255, 0), matrix->Color(0, 0, 255) };

const uint16_t blue = matrix->Color(0,0,255);
const uint16_t green = matrix->Color(0, 255, 0);
const uint16_t red = matrix->Color(255, 0, 0);
const uint16_t clear = matrix->Color(0,0,0);
uint16_t COLOR = blue;

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
  mouth = 'w';
  makeOwO1();
}

int x    = mw;
int pass = 0;

void loop() {
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    switch (incomingByte)
      {
        case 'h':
          mouth = 'h';
          makeDraw(COLOR, mouth);
          break;
        case 's':
          mouth = 's';
          makeDraw(COLOR,mouth);
          break;
        case 'l':
          mouth = 'l';
          makeDraw(COLOR,mouth);
          break;
        case '1':
          makeBlink();
          break;
        case '2':
          //not hungry
          COLOR = matrix->Color(96, 73, 183);
          makeDraw(COLOR,mouth);
          break;
        case '3':
          //slightly hungry
          COLOR = matrix->Color(192, 174, 39);
          makeDraw(COLOR,mouth);
          break;
        case '4':
          //extremely hungry
          COLOR = matrix->Color(30,123,30);
          makeDraw(COLOR,mouth);
          break;
        case 'd':
          mouth = 'w';
          COLOR = blue;
          makeOwO1();
          break;
      }
  }
}


void makeDraw(uint16_t color, char mouth){
  matrix->clear();
  makeMouth(color,mouth);
  makeEyes(color);
  matrix->show();
}

void makeMouth(uint16_t color,char mouth){
  if(mouth == 'w'){
    matrix->drawPixel(1,6,color);
    matrix->drawPixel(2,7,color);
    matrix->drawPixel(3,6,color);
    matrix->drawPixel(4,7,color);
    matrix->drawPixel(5,6,color);
  }
  else if(mouth == 's'){
    matrix->drawPixel(1,7,color);
    matrix->drawPixel(6,7,color);
    matrix->drawFastHLine(1,6,6,color);
  }
  else if(mouth == 'h'){
    matrix->drawPixel(1,6,color);
    matrix->drawPixel(6,6,color);
    matrix->drawLine(1,7,6,7,color);
  }
  else if(mouth == 'l'){
    matrix->drawFastHLine(1,6,6,color);
  }
}

void makeEyes(uint16_t color){
    matrix->drawRoundRect(0,0,3,4,1,color);
    matrix->drawRoundRect(5,0,3,4,1,color);
}

void makeOwO1(){
  matrix->clear();
  makeMouth(COLOR,mouth);
  matrix->drawRoundRect(0,0,3,4,1,COLOR);
  matrix->drawRoundRect(5,0,3,4,1,COLOR);
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
  makeMouth(COLOR,mouth);
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
