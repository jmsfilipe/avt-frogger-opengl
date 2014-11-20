#include "BodyPart.h"


BodyPart::BodyPart(float *color, float shininess, float *size, 
                   float *position, float *rotation) {
    _vsSurfRev = new VSResSurfRevLib();

    setEstimatedColor(ColorProperty::AMBIENT, color);
    setEstimatedColor(ColorProperty::DIFFUSE, color);
    setEstimatedColor(ColorProperty::SPECULAR, color);

    _shininess[0] = shininess;

    setDimensions(_size, size);
    setDimensions(_position, position);
    setRotation(rotation);
}

BodyPart::~BodyPart(void) { }

VSResSurfRevLib *BodyPart::getSurfRev() {
    return _vsSurfRev;
}

float BodyPart::getSize(int dimension) {
    return _size[dimension];
}

float *BodyPart::getSize() {
    return _size;
}

float BodyPart::getPosition(int dimension) {
    return _position[dimension];
}

float* BodyPart::getPosition() {
    return _position;
}

float BodyPart::getRotation(int axis) {
    return _rotation[axis];
}

float* BodyPart::getRotation() {
    return _rotation;
}

void BodyPart::setupMaterials() {
    getSurfRev()->setMaterialBlockName("Materials");
    getSurfRev()->setColor(VSResourceLib::AMBIENT, _ambColor);
    getSurfRev()->setColor(VSResourceLib::DIFFUSE, _diffColor);
    getSurfRev()->setColor(VSResourceLib::SPECULAR, _specColor);
    getSurfRev()->setColor(VSResourceLib::SHININESS, _shininess);
}

void BodyPart::draw() { }

void BodyPart::update() { }

// AUXILIARY FUNCTIONS //////////////////////////////////////////////

void BodyPart::setEstimatedColor(ColorProperty component, float *baseColor) {
    float *auxColor;
    int factor;
    
    switch (component)
    {
    case ColorProperty::AMBIENT:
        auxColor = _ambColor;
        return;
        break;
    case ColorProperty::DIFFUSE:
        factor = 0.1;
        auxColor = _diffColor;
        break;
    case ColorProperty::SPECULAR:
        factor = 0.25;
        auxColor = _specColor;
        break;
    default:
        return;
        break;
    }

    brightenColor(auxColor, baseColor, 1.0 + factor);

}

void BodyPart::setColor(float *orig, float *newColor) {
    orig[R] = newColor[R];
    orig[G] = newColor[G];
    orig[B] = newColor[B];
    orig[A] = newColor[A];
}

void BodyPart::brightenColor(float *orig, float *newColor, 
                             float brighteningFactor) {

    if(orig != NULL)
        setColor(orig, newColor);
    else
        return;

    orig[R] *= brighteningFactor;
    orig[G] *= brighteningFactor;
    orig[B] *= brighteningFactor;
}

void BodyPart::setDimensions(float *orig, float *newDimensions) {
    orig[SpatialProperty::X] = newDimensions[SpatialProperty::X];
    orig[SpatialProperty::Y] = newDimensions[SpatialProperty::Y];
    orig[SpatialProperty::Z] = newDimensions[SpatialProperty::Z];
}

void BodyPart::changeSize(float *newSize) {
    _size[X] = newSize[X];
    _size[Y] = newSize[Y];
    _size[Z] = newSize[Z];
}

void BodyPart::setRotation(float *newRotation) {
    _rotation[SpatialProperty::ANGLE] = newRotation[SpatialProperty::ANGLE];
    _rotation[SpatialProperty::AX] = newRotation[SpatialProperty::AX];
    _rotation[SpatialProperty::AY] = newRotation[SpatialProperty::AY];
    _rotation[SpatialProperty::AZ] = newRotation[SpatialProperty::AZ];
}