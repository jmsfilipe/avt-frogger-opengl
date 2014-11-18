#pragma once 

#include "vsMathLib.h"
#include "vsShaderLib.h"
#include "vsResSurfRevLib.h"

#define LEFT_LIMIT 30
#define RIGHT_LIMIT -30
#define UP_LIMIT 30
#define DOWN_LIMIT -30

#define TIMBERLOG_SPEED 0.006f
#define FROG_SPEED 0.006f
#define TURTLE_SPEED 0.003f
#define BUS_SPEED 0.004f
#define CAR_SPEED 0.005f

enum RiverRow {CAR_ONE, BUS_ONE, CAR_TWO, CAR_THREE, BUS_TWO, TURTLE_ONE, LOG_ONE, LOG_TWO, TURTLE_TWO, LOG_THREE};

enum ColorProperty {R = 0, G, B, A, RGBA, AMBIENT = 0, DIFFUSE, SPECULAR};

enum SpatialProperty {X, Y, Z, XYZ, ANGLE = 0, AX, AY,AZ, AXYZ, RADIUS = 0, HEIGHT, MORE_FILLER = 1, FILLER};

class Lib{

public:
static VSMathLib *vsml;

//random including max and min
static int random(int min, int max);
static float random(float a, float b);

};

