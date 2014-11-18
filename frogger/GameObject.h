#pragma once

#include "Entity.h"
#include "BoundingBox.h"

typedef VSResSurfRevLib Part;
typedef std::vector<Part*> Parts;

class GameObject : public Entity {
protected:
public:
	int _iTex;
	std::string _texPath;
	int _texID;
protected:
    Parts *_parts;
	float *_diffColor, *_ambColor, *_specColor, *_shininess;
    enum MaterialColorComponents {
        AMBIENT_COMP = 0, DIFFUSE_COMP, SPECULAR_COMP, N_COMPONENTS
    };
    enum ColorConstants {
        R = 0, G, B, RGBA = 4
    };
	BoundingBox _box;
public:
	GameObject();
    GameObject(int nParts);
    GameObject(float *ambColor, float *diffColor, float *specColor, float shine, int nParts);

    Part *getPart(int part);
    Parts *getParts();

	virtual void update();
    virtual void draw();
    void setBaseColor(int component, float *color);
    void setShininess(float shine);

	bool collide(BoundingBox b);
	BoundingBox getBox();
	
	virtual void updateBoundingBox();

	
	void setTexture(int i, std::string path);
};