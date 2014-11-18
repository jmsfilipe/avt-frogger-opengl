#pragma once
#include "bodypart.h"
class CylindricalBodyPart : public BodyPart {
    enum CylinderProperties {
        RADIUS, HEIGHT
    };

public:
    CylindricalBodyPart(float *color, float shininess, float *size,
        float *pos, float *rot);
    CylindricalBodyPart(float *ambColor, float *diffColor, float *specColor,
        float shininess, float *size, float *pos, float *rot);
    ~CylindricalBodyPart(void);

    void draw();
    void update();
};
