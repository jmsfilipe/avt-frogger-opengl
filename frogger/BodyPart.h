#pragma once

#include "vsResSurfRevLib.h"
#include "Lib.h"

class BodyPart {
private:
    VSResSurfRevLib *_vsSurfRev;

    float _ambColor[RGBA], _diffColor[RGBA], _specColor[RGBA], _shininess[1];
    float _size[XYZ], //x, y, z but can be read as radius, height, z
        _position[XYZ],
        _rotation[AXYZ];//4 positions: angle, x,y,z

protected:
    static const int _sides = 10;

public:
    BodyPart(float *color, float shininess, float *size, 
        float *position, float *rotation);

    ~BodyPart(void);

    VSResSurfRevLib *getSurfRev();

    float getSize(int dimension);
    float *getSize();

    float getPosition(int dimension);
    float *getPosition();

    float getRotation(int axis);
    float *getRotation();

    virtual void draw();

    virtual void update();

    void setupMaterials();

    // AUXILIARY FUNCTIONS //////////////////////////////////////////

    /** Sets a specified color component based on a given base, ambient
     * color. Made on the assumption that the diffuse would generally
     * be a brighter color than the ambient, and the specular would be
     * even brighter.
     * \param an indicator of the component to estimate
     * \param a float array containing a rgba color
     */
    void setEstimatedColor(ColorProperty component, float *baseColor);

    /** Sets the rgba values based on the given color
     */
    void setColor(float *orig, float *newColor);

    void brightenColor(float *orig, float *newColor, 
        float brighteningFactor);

    void setDimensions(float *orig, float *dimensions);

    void changeSize(float *newSize);

    void setRotation(float *rotation);
};

