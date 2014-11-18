#pragma once
#include "bodypart.h"

class SphericalBodyPart : public BodyPart {
    enum Dimensions {
        RADIUS
    };

public:
    SphericalBodyPart(float *color, float shininess, float *size,
        float *pos, float *rot);
    SphericalBodyPart(float *ambColor, float *diffColor, float *specColor,
        float shininess, float *size, float *pos, float *rot);
    ~SphericalBodyPart();

    float getRadius();
    int getSides();

    void draw();
    void update();
};

