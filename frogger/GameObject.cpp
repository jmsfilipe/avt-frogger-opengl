#include "GameObject.h"

GameObject::GameObject() : Entity(){
    _parts = new Parts();

	_diffColor = new float[4]();
    _ambColor = new float[4]();
    _specColor = new float[4]();
    _shininess = new float[1]();
}

GameObject::GameObject(int nParts) {
    _parts = new Parts();

    for(int i = 0; i < nParts; i++) {
        _parts->push_back(new Part());
    }

    _diffColor = new float[4]();
    _ambColor = new float[4]();
    _specColor = new float[4]();
    _shininess = new float[1]();
}

GameObject::GameObject(float *amb, float *diff, float *spec, float shine, int nParts) : Entity() {
    _parts = new Parts();

    for(int i = 0; i < nParts; i++) {
        _parts->push_back(new Part());
    }

    _diffColor = new float[4]();
    _ambColor = new float[4]();
    _specColor = new float[4]();
    _shininess = new float[1]();

    setBaseColor(AMBIENT_COMP, amb);
    setBaseColor(DIFFUSE_COMP, diff);
    setBaseColor(SPECULAR_COMP, spec);
    setShininess(shine);
}

/**
 * throws: out_of_range exception if body part does not exist
 */
Part *GameObject::getPart(int part) {
    return _parts->at(part); //index out of bounds exception ready
}

/**
 * Virtual function to be overridden
 */
void GameObject::update() {
    return;
}

/**
 * Virtual function to be overridden
 */
void GameObject::draw() {
    return;
}

void GameObject::estimateColors(float *color) {
	_ambColor[0] = color[0];
    _ambColor[1] = color[1];
    _ambColor[2] = color[2];
    _ambColor[3] = color[3];

	_diffColor[0] = color[0] * 1.1;
    _diffColor[1] = color[1] * 1.1;
    _diffColor[2] = color[2] * 1.1;
    _diffColor[3] = color[3];

	_specColor[0] = color[0] * 1.25;
    _specColor[1] = color[1] * 1.25;
    _specColor[2] = color[2] * 1.25;
    _specColor[3] = color[3];
}

void GameObject::estimateColors(float *color, float *amb, float *diff, float *spec) {
	amb[R] = color[0];
	amb[G] = color[1];
	amb[B] = color[2];
	amb[A] = color[3];

	diff[R] = color[0] * 1.1;
	diff[G] = color[1] * 1.1;
	diff[B] = color[2] * 1.1;
	diff[A] = color[3];

	spec[0] = color[0] * 1.25;
    spec[1] = color[1] * 1.25;
    spec[2] = color[2] * 1.25;
    spec[3] = color[3];
}


void GameObject::setBaseColor(int component, float *color) {
    switch (component)
    {
    case AMBIENT_COMP:
        _ambColor[0] = color[0];
        _ambColor[1] = color[1];
        _ambColor[2] = color[2];
        _ambColor[3] = color[3];
        break;
    case DIFFUSE_COMP:
        _diffColor[0] = color[0];
        _diffColor[1] = color[1];
        _diffColor[2] = color[2];
        _diffColor[3] = color[3];
        break;
    case SPECULAR_COMP:
        _specColor[0] = color[0];
        _specColor[1] = color[1];
        _specColor[2] = color[2];
        _specColor[3] = color[3];
        break;
    default:
        std::cout << "Error setting object color: " << 
            component << " is not a known object color component." << std::endl;
        break;
    }
}

void GameObject::setShininess(float shine) {
    _shininess[0] = shine;
}

void GameObject::updateBoundingBox() {
    return;
}

bool GameObject::collide(BoundingBox b){
	return _box.AABBtoAABB(b);
}

BoundingBox GameObject::getBox(){
	return _box;
}

void GameObject::setTexture(int i, std::string path) {
	_iTex=i;
	_texPath = path;
}

