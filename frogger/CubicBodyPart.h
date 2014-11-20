#pragma once

#include "BodyPart.h"

class CubicBodyPart : public BodyPart {
public:
    CubicBodyPart(float *color, float shininess, float *size,
        float *pos, float *rot);
    ~CubicBodyPart(void);

    void draw();
    void update();
};
