#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>
#pragma comment(lib, "glew32.lib")

#define CAPTION "Frogger AVT"
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;

//Shapes
#include "Frog.h"
#include "TimberLog.h"
#include "Car.h"
#include "Bus.h"
#include "Turtle.h"
#include "Roadside.h"
#include "Road.h"
#include "River.h"
#include "Riverside.h"
#include "LightSource.h"
#include "vsFontLib.h"

#define OBJS_PER_ROW 3

#define TIMERMSECS 60

#define LIFES 5

int totalLifes = LIFES;
int totalPoints = 0;
bool gameOver = false;

//LIGHTS
LightSource _directionalLight;
LightSource _pointLight[6];
LightSource _spotLight;

//COLORS
float TIMBERLOG_COLOR[4] = {0.6f, 0.4f, 0.12f, 1.0f};
float FROG_COLOR[4] = {0.0f, 1.0f, 0.0f, 1.0f};
float TURTLE_COLOR[4] = {1.0f, 0.0f, 0.0f, 1.0f};
float BUS_COLOR[4] = {0.0f, 0.0f, 1.0f, 1.0f};
float CAR_COLOR[4] = {0.98f, 0.625f, 0.12f, 1.0f};

VSResSurfRevLib pawn;
VSShaderLib shader, shaderF;

float startTime;
float prevTime;

float elapsed = 1.0f; 

// Camera Position
float camX = 0, camY = 0, camZ = 0;

// Mouse Tracking Variables
int startX, startY, tracking = 0;

// Camera Spherical Coordinates
float alpha = 39.0f, beta = 51.0f;
float r = 10.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f, deltaAngleUp = 0.0f;
int xOrigin = -1, yOrigin = -1;

// camera perspective/ortho
enum CameraProjection {PERSPECTIVE, ORTHO, MOBILE};
int camera;

//Frog
Frog *frog;
float frogSpeed[3] = {FROG_SPEED, 0.0f, FROG_SPEED};
enum Movement {LEFT, RIGHT, FRONT, BACK};
int frogMovement = -1;
double objx = 0, objy = 0, objz = 0;

//Objects

std::vector<TimberLog *> *timberlogs;
std::vector<Turtle *> *turtles;
std::vector<Bus *> *buses;
std::vector<Car *> *cars;

Roadside *bottomRoadside, *upperRoadside;
Road *road;
River *river;
Riverside *upperRiverside;

//NIGHT MODE
int _spotLightOn = 0, _directionalLightOn = 0, _pointLightOn = 0;

VSFontLib vsfl;
unsigned int lifes, points, gameover;

GLint YES = 1;
GLint NO = 0;

float eyeDirection[3];
