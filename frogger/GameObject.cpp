#include "GameObject.h"

GameObject::GameObject() : Entity(){
    _body = new Body();
}

Body *GameObject::getBody() {
    return _body;
}

BoundingBox GameObject::getBox(){
	return _box;
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

void GameObject::updateBoundingBox() {
    return;
}

bool GameObject::collide(BoundingBox b){
	return _box.AABBtoAABB(b);
}
