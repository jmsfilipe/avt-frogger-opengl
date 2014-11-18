#pragma once

#include <iostream>
#include "Lib.h"
#include "BodyPart.h"
#include "SphericalBodyPart.h"
#include "CylindricalBodyPart.h"
#include "CubicBodyPart.h"

class BodyParts {
    friend class CubicBodyPart;
    std::vector<BodyPart *> _parts;
public:
    BodyParts();
    ~BodyParts();
    
    void addCubicPart(float *baseColor, float shininess, 
        float *size, float *posInBody, float rotationAngle, float *rotationAxis);

    void addSphericalPart(float *baseColor, float shininess ,
        float radius, float *posInBody);
    
    void addCylindricPart(float *baseColor, float shininess, 
        float height, float radius, float *posInBody, float rotationAngle, 
        float *rotationAxis);

    void draw();
    void update();
};

