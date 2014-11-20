#pragma once

#include "Entity.h"
#include "BoundingBox.h"
#include "Body.h"

typedef VSResSurfRevLib Part;
typedef std::vector<Part*> Parts;

class GameObject : public Entity {
    Body *_body;
	public:
	int _iTex;
	std::string _texPath;
	int _texID;
protected:
	BoundingBox _box;
public:
	GameObject();

    Body *getBody();
    BoundingBox getBox();

	virtual void update();
    virtual void draw();

	bool collide(BoundingBox b);
	virtual void updateBoundingBox();
		void setTexture(int i, std::string path);
};