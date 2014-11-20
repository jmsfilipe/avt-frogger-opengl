#pragma once 

#include "vsMathLib.h"
#include "vsShaderLib.h"
#include "vsResSurfRevLib.h"

#define LEFT_LIMIT 30
#define RIGHT_LIMIT -30
#define UP_LIMIT 30
#define DOWN_LIMIT -30
#define ROADSIDE_WIDTH 5.0
#define ROAD_WIDTH 20.0
#define RIVERSIDE_WIDTH 5.0
#define RIVER_WIDTH 25.0

#define ROAD_ROWS 5
#define RIVER_ROWS 5

#define MARGINAL_SPACE 0.05

static const float BOARD_LENGTH = LEFT_LIMIT - RIGHT_LIMIT;
static const float BOARD_HEIGHT = UP_LIMIT - DOWN_LIMIT;
static const float LEFT_SPAWN_LIMIT = LEFT_LIMIT + 5.0;
static const float RIGHT_SPAWN_LIMIT = RIGHT_LIMIT - 5.0;

static const float ROADLANE_WIDTH = ROAD_WIDTH / ROAD_ROWS;
static const float RIVER_ROW_WIDTH = RIVER_WIDTH / RIVER_ROWS;

static const float ROAD_INBETWEEN_SPACE = 0.05 * ROADLANE_WIDTH;
static const float RIVER_INBETWEEN_SPACE = 0.05 * RIVER_ROW_WIDTH;

static const float ROAD_BOTTOM = DOWN_LIMIT + ROADSIDE_WIDTH;
static const float RIVER_BOTTOM = UP_LIMIT - RIVERSIDE_WIDTH - RIVER_WIDTH;

#define TIMBERLOG_SPEED 0.006f
#define FROG_SPEED 0.006f
#define TURTLE_SPEED 0.003f
#define BUS_SPEED 0.004f
#define CAR_SPEED 0.005f

enum RiverRow {CAR_ONE, BUS_ONE, CAR_TWO, CAR_THREE, BUS_TWO, TURTLE_ONE, LOG_ONE, LOG_TWO, TURTLE_TWO, LOG_THREE};

enum ColorProperty {R = 0, G, B, A, RGBA, AMBIENT = 0, DIFFUSE, SPECULAR, COLOR_COMPONENTS};

enum SpatialProperty {X, Y, Z, XYZ, ANGLE = 0, AX, AY,AZ, AXYZ, RADIUS = 0, HEIGHT, MORE_FILLER = 1, FILLER};

class Lib{

public:
static VSMathLib *vsml;

//random including max and min
static int random(int min, int max);
static float random(float a, float b);

};

