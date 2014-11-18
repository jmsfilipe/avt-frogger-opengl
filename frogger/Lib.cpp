#pragma once

#include "Lib.h"

VSMathLib *Lib::vsml = VSMathLib::getInstance();

//random including max and min
int Lib::random(int min, int max){
return rand()%(max-min + 1) + min;
}

float Lib::random(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}