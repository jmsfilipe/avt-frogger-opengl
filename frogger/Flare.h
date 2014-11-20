#ifndef _FLARE_H_
#define _FLARE_H_

#include "VSMathlib.h"
#include "VSShaderlib.h"
#include "VSResSurfRevLib.h"

/* --- Defines --- */

#define FLARE_MAXELEMENTSPERFLARE         15

#define FLARE_RANGE(A,B)    ( (rand()%((B)-(A)+1)) + (A) )
#define FLARE_FRANGE(A,B)   ( ((float)(rand()&0xffffff)/(float)0xfffffe)*((B)-(A)) + (A) )

#define MAKEID(a,b,c,d)     (((a)<<24) | ((b)<<16) | ((c)<<8) | ((d)<<0))

/* --- Types --- */

typedef struct FLARE_ELEMENT_DEF
{
    struct TEXTURE_DEF  *texture;

    float           fDistance;        // Distance along ray from source (0.0-1.0)
    float           fSize;            // Size relative to flare envelope (0.0-1.0)
    unsigned int    argb;            // ARGB for intensity mapping
} FLARE_ELEMENT_DEF;

typedef struct FLARE_DEF
{
    float           fScale;     // Scale factor for adjusting overall size of flare elements.
    float           fMaxSize;   // Max size of largest element, as proportion of screen width (0.0-1.0)
    int             nPieces;    // Number of elements in use


    FLARE_ELEMENT_DEF    element[FLARE_MAXELEMENTSPERFLARE];
} FLARE_DEF;

/* --- Prototypes --- */
class Flare
{
public:
	Flare();
	void FLARE_render(float cosine);
	void FLARE_init();
	void FLARE_position(int x, int y);
	void drawQuad( int x, int y, int width, int height, TEXTURE_DEF *tex, unsigned int colour );
	VSResSurfRevLib surfRev;
private:
	
};

#endif
