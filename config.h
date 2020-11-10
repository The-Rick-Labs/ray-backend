#include <FastLED_NeoMatrix.h>
#include <FastLED.h>

#define MATRIX_TILE_HEIGHT  8
#define MATRIX_TILE_WIDTH   8
#define MATRIX_TILE_H       1  
#define MATRIX_TILE_V       1  

#define mw (MATRIX_TILE_WIDTH * MATRIX_TILE_H)
#define mh (MATRIX_TILE_HEIGHT * MATRIX_TILE_V)

#define NUMMATRIX (mw*mh)

#define brightness 32