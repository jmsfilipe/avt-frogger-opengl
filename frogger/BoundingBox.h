#pragma once

class BoundingBox {
protected:
	float _vecMin[3];
	float _vecMax[3];
public:
	BoundingBox();
	~BoundingBox();
	void setMin(float x, float y, float z);
	void setMax(float x, float y, float z);
	bool AABBtoAABB(BoundingBox b);
};