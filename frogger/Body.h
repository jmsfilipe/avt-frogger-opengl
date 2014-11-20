#pragma once

#include <iostream>
#include "Lib.h"
#include "BodyPart.h"
#include "SphericalBodyPart.h"
#include "CylindricalBodyPart.h"
#include "CubicBodyPart.h"

class Body {
    std::vector<BodyPart *> _bodyParts;
public:
    float defaultPos[XYZ];
    float defaultSize[XYZ];
    float defaultRot[AXYZ];

    Body();
    ~Body();
    
    void addCubicPart(float *baseColor, float shininess, 
        float *size, float *posInBody, float rotationAngle, float *rotationAxis);

    void addCubicPart(float *baseColor, float shininess, 
        float *size, float *posInBody);

    void addCubicPart(float *baseColor, float shininess, 
        float *size);

    void addSphericalPart(float *baseColor, float shininess ,
        float radius, float *posInBody);
    
    void addCylindricPart(float *baseColor, float shininess, 
        float height, float radius, float *posInBody, float rotationAngle, 
        float *rotationAxis);

    void addCylindricPart(float *baseColor, float shininess, 
        float height, float radius, float *posInBody);

    void addCylindricPart(float *baseColor, float shininess, 
        float height, float radius);

    BodyPart *getBodyPart(int part);

    void draw();
    void update();
};

