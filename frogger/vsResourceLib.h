/** ----------------------------------------------------------
 * \class VSResourceLib
 *
 * Lighthouse3D
 *
 * VSResourceLib - Very Simple Resource Library
 *
 * \version 0.1.1
 *		Added virtual function load cubemaps
 *		Added virtual function to set a preloaded texture
 *		Added a virtual clone method
 *
 * version 0.1.0
 *		Initial Release
 *
 * This abstract class defines an interface 
 * for loading and rendering resources (models)
 *
 * This lib requires the following classes from VSL:
 * (http://www.lighthouse3d.com/very-simple-libs)
 *
 * VSMathLib 
 * VSLogLib
 * VSShaderLib
 *
 * and the following third party libs:
 *
 * GLEW (http://glew.sourceforge.net/),
 * DevIL (http://openil.sourceforge.net/) (optional)
 *
 * Full documentation at 
 * http://www.lighthouse3d.com/very-simple-libs
 *
 ---------------------------------------------------------------*/

#ifndef __VSRL__
#define __VSRL__

#include <string>
#include <vector>
#include <map>
#include <fstream>


#include <GL/glew.h>

#define _VSL_TEXTURE_WITH_DEVIL


#ifdef _VSL_TEXTURE_WITH_DEVIL
// include DevIL for image loading
#include <IL/il.h>
#endif

#ifdef _WIN32
#pragma comment(lib,"glew32.lib")
#ifdef _VSL_TEXTURE_WITH_DEVIL
#pragma comment(lib,"devil.lib")
#endif
#endif

// Include other VSL
// vsMathLib is required for rendering and matrix manipulation
#include "vsMathLib.h"
// vsLogLib is required for logging errors and model info
#include "vsLogLib.h"
// VSShaderLib is required to enable and set the 
// semantic of the vertex arrays
#include "vsShaderLib.h"


class VSResourceLib {

protected:

	/// helper structure for derived classes
	struct Material{

		float diffuse[4];
		float ambient[4];
		float specular[4];
		float emissive[4];
		float shininess;
		int texCount;
	};

public:

	/// material semantics
	enum MaterialSemantics {

		DIFFUSE,
		AMBIENT,
		SPECULAR,
		EMISSIVE,
		SHININESS,
		TEX_COUNT
	} MaterialComponent;

	VSResourceLib();
	~VSResourceLib();

	/** clones the resource - must be implemented 
	* by the subclasses to take effect
	* \param res the instance to be cloned into this
	*/
	virtual void clone(VSResourceLib *res) {res = NULL;};

	/// load the resource
	virtual bool load(std::string filename) = 0;

	/// render the resource
	virtual void render() = 0;

#ifdef _VSL_TEXTURE_WITH_DEVIL
	/// virtual function to be implemented in derived classes
	/// assigns a texture (from an image) to a unit
	virtual int addTexture(unsigned int unit, std::string filename) {return 0;};
	virtual void addCubeMapTexture(unsigned int unit, 
									std::string posX, std::string negX, 
									std::string posY, std::string negY, 
									std::string posZ, std::string negZ) {};
	virtual void setTexture(unsigned int unit, unsigned int textureID,
							GLenum textureType = GL_TEXTURE_2D) {};

#endif
	/// const to ease future upgrades
	static const int MAX_TEXTURES = 8;
	/// Sets the shader's material block name
	void setMaterialBlockName(std::string);


	/// set the semantics of the uniforms inside the named block
	void setUniformSemantics(MaterialSemantics field, std::string);

	/// returns errors found when loading the resource
	/// it is up to the derived classes to add meaningfull
	/// information
	virtual std::string getErrors();
	/// returns information about the loaded resource
	/// it is up to the derived classes to add meaningfull
	/// information
	virtual std::string getInfo();
	/// returns the scale factor to display the model in a unit cube
	/// note: may not apply to all subclasses
	float getScaleForUnitCube();

#ifdef _VSL_TEXTURE_WITH_DEVIL
	/// helper function for derived classes
	static unsigned int loadRGBATexture(std::string filename, bool mipmap = true,
					bool compress = false,
					GLenum aFilter = GL_LINEAR, GLenum aRepMode = GL_REPEAT);
	static unsigned int loadCubeMapTexture(	std::string posX, std::string negX, 
									std::string posY, std::string negY, 
									std::string posZ, std::string negZ);
	static GLenum faceTarget[6];
#endif

	virtual void renderBB();

protected:

	static VSLogLib mLogError, mLogInfo;
	/// set the material uniforms
	void setMaterial(Material &aMat);


	std::map<std::string, MaterialSemantics> mMatSemanticMap;

	/// shader's material block name
	std::string mMaterialBlockName;

	/// keep a pointer to VSMathLib singleton
	VSMathLib *mVSML;
	/// Logs for errors and model Information

	/// center of the model
	float mCenter[3];	
	/// scale factor for the model to fill a unit cube (-1, 1)
	float mScaleToUnitCube;

	void initBB();

	GLuint bbVAO;
	bool bbInit;
	float bb[2][3];
};

#endif
