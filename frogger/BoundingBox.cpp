#pragma once

#include "BoundingBox.h"

BoundingBox::BoundingBox(){

}

BoundingBox::~BoundingBox(){
}

bool BoundingBox::AABBtoAABB(BoundingBox b){
	//Check if Box1's max is greater than Box2's min and Box1's min is less than Box2's max (if they collide)
    return(_vecMax[0] > b._vecMin[0] && 
    _vecMin[0] < b._vecMax[0] &&
    _vecMax[1] > b._vecMin[1] &&
    _vecMin[1] < b._vecMax[1] &&
    _vecMax[2] > b._vecMin[2] &&
    _vecMin[2] < b._vecMax[2]);

//If not, it will return false
}

void BoundingBox::setMax(float x, float y, float z){
	_vecMax[0] = x;
	_vecMax[1] = y;
	_vecMax[2] = z;
}

void BoundingBox::setMin(float x, float y, float z){
	_vecMin[0] = x;
	_vecMin[1] = y;
	_vecMin[2] = z;
}

