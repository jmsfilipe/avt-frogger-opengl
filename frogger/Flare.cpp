/* Copyright (C) Yossarian King, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Yossarian King, 2000"
 */
/************************************************************

    Game Programming Gems
    Lens Flare Demo

    Y. King / May 2000
    Electronic Arts Canada, Inc.

 ************************************************************/

//#include <GLUT/gl.h>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <string.h>

#include "flare.h"

/************************************************************
    Defines.
 ************************************************************/

// Get height from width, assuming certain aspect ratio.
#define HEIGHTFROMWIDTH(w)  ((320*(w)*SCREENheight)/(240*SCREENwidth))

#define isqrt(x)        (int)((double)(x))

/************************************************************
    Texture management.
 ************************************************************/

typedef struct TEXTURE_DEF
{
    char    *filename;
    int     width;
    int     height;
    void    *pixels;
    unsigned char   *memory;        // file buffer; free this when done with texture
}
    TEXTURE_DEF;

// Texture enumeration -- matches the data that gets loaded.
enum
{
    TEX_CRCL,
    TEX_HXGN,
    TEX_RING,
    TEX_FLAR,

    NPIECETEXTURES,

    TEX_SUN = NPIECETEXTURES,
    TEX_BACK,

    NTEXTURES
};

// Source files for textures.
TEXTURE_DEF gTextures[ NTEXTURES ] =
            {
                { "flare/crcl.jpg" },
                { "flare/hxgn.jpg" },
                { "flare/ring.jpg" },
                { "flare/flar.jpg" },
                { "flare/sun.jpg"  },
                { "flare/back.jpg" }
            };

TEXTURE_DEF *TM_getNthTexture( int n );
TEXTURE_DEF *TM_getNamedTexture( char *name );
void        TM_loadTextures( void );
void        TM_purgeTextures( void );
void        TM_setTexture( TEXTURE_DEF *tex );

/************************************************************
    Internal function prototypes.
 ************************************************************/

//void    drawQuad( int x, int y, int width, int height, TEXTURE_DEF *tex, unsigned int colour );

/************************************************************
    Global variables.
 ************************************************************/

int     SCREENwidth = 640;
int     SCREENheight = 480;

/************************************************************

    Public:
        FLARE_randomize

    Description:
        Generate a random lens flare.

 ************************************************************/

void    FLARE_randomize(FLARE_DEF *flare,
                        int nTextures,
                        int nPieces,
                        float fMaxSize,
                        unsigned int minColour,
                        unsigned int maxColour)
{
    int             i;
    float           fFracDist;
    float           fEnvelopeSize;
    FLARE_ELEMENT_DEF *element;

    // Initialize flare with requested number of elements, with
    // random placement, colour, and size of elements.
    flare->nPieces = nPieces;
    flare->fScale = fMaxSize;
    flare->fMaxSize = fMaxSize;
    fFracDist = 1.0f/(float)(flare->nPieces - 1);
    
    for (i = 0; i < flare->nPieces; ++i)
    {
        element = &flare->element[i];
        element->fDistance = (fFracDist*i) + FLARE_FRANGE(0,fFracDist);

        // Envelope size is maximum at ends of line, minimum in the middle (i.e. two
        // cones, touching at the tips).
        fEnvelopeSize = (float)fabs(1.0f - 2*element->fDistance);

        element->fSize = FLARE_FRANGE(0.6f, 1.0f) * fEnvelopeSize;
        element->argb = FLARE_RANGE(minColour & 0xff000000, maxColour & 0xff000000) |
                      FLARE_RANGE(minColour & 0x00ff0000, maxColour & 0x00ff0000) |
                      FLARE_RANGE(minColour & 0x0000ff00, maxColour & 0x0000ff00) |
                      FLARE_RANGE(minColour & 0x000000ff, maxColour & 0x000000ff);
        //element->texture = TM_getNthTexture( FLARE_RANGE(0, nTextures - 1) );
    }
}


/*
    drawQuad -- used to draw individual elements of the lens flare
    in 2D. This is the main thing that needs to be changed to render
    with a different engine (e.g. D3D instead of OpenGL).
*/

void    Flare::drawQuad( int x, int y, int width, int height, TEXTURE_DEF *tex, unsigned int colour )
{
	VSMathLib* vsml = VSMathLib::getInstance();

	//surfRev.addTexture(0, tex->filename);
		surfRev.setMaterialBlockName("Materials");
	float f1[1] = {100};
	float f[4] = {colour >> 16 & 0xff, colour >> 8 & 0xff,colour >> 0 & 0xff, colour >> 24 & 0xff};
	surfRev.setColor(VSResourceLib::DIFFUSE, f);
	float f2[4] = {colour >> 16 & 0xff, colour >> 8 & 0xff,colour >> 0 & 0xff, colour >> 24 & 0xff};
	surfRev.setColor(VSResourceLib::SPECULAR, f2);
	float f3[4] = {colour >> 16 & 0xff, colour >> 8 & 0xff,colour >> 0 & 0xff, colour >> 24 & 0xff};
	surfRev.setColor(VSResourceLib::AMBIENT, f3);
	surfRev.setColor(VSResourceLib::SHININESS,f1);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(x,y, 0.0f);
	vsml->scale(width,height,0.0f);
	surfRev.render();
	vsml->popMatrix(VSMathLib::MODEL);
}


// -------------- texture manager ---------------

TEXTURE_DEF *TM_getNthTexture( int n )
{
    if ( ( n < 0 ) || ( n >= NTEXTURES ) )
        return NULL;

    return &gTextures[n];
}

TEXTURE_DEF *TM_getNamedTexture( char *name )
{
    int     i;

    for ( i = 0; i < NTEXTURES; ++i )
    {
        if ( strncmp( name, gTextures[i].filename, strlen( name ) ) == 0 )
            return &gTextures[i];
    }

    return NULL;
}

void    TM_loadTextures( void )
{
    int             i;

    TEXTURE_DEF *tex = &gTextures[0];

    for ( i = 0; i < NTEXTURES; ++i, ++tex )
    {
        FILE    *f = fopen( tex->filename, "rb" );
        int     nBytes;

        tex->height = 0;
        tex->width = 0;
        tex->pixels = NULL;
        tex->memory = NULL;

        if ( f )
        {
            int             j;
            unsigned char   *ppix;

            // Find file length by seeking to end of file.
            fseek( f, 0, SEEK_END );
            nBytes = ftell( f );
            fseek( f, 0, SEEK_SET );

            tex->memory = (unsigned char *)malloc( nBytes );
            fread( tex->memory, 1, nBytes, f );
            fclose( f );

            // Read little-endian texture sizes in machine-independent way.
            tex->width  = ( tex->memory[1] << 8 ) | ( tex->memory[0] );
            tex->height = ( tex->memory[3] << 8 ) | ( tex->memory[2] );
            tex->pixels = tex->memory + 4;

            // Fix ARGB --> RGBA pixel byte order to suit OpenGL pixel format.
            j = tex->width * tex->height;
            ppix = (unsigned char *)tex->pixels;
            while ( j-- )
            {
                unsigned char b = ppix[0];
                unsigned char g = ppix[1];
                unsigned char r = ppix[2];
                unsigned char a = ppix[3];

                ppix[0] = r;
                ppix[1] = g;
                ppix[2] = b;
                ppix[3] = a;

                ppix += 4;
            }
        }
    }
}

void        TM_purgeTextures( void )
{
    int         i;
    TEXTURE_DEF *tex = &gTextures[0];

    for ( i = 0; i < NTEXTURES; ++i, ++tex )
    {
        if ( tex->memory )
            free( tex->memory );
    }
}

void        TM_setTexture( TEXTURE_DEF *tex )
{
    if ( tex )
    {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glEnable( GL_TEXTURE_2D );
        glTexImage2D(   GL_TEXTURE_2D,
                        0,                  // level
                        4,                  // components
                        tex->width,
                        tex->height,
                        0,                  // border
                        GL_RGBA,            // format
                        GL_UNSIGNED_BYTE,   //type
                        tex->pixels );
    }
    else
    {
        glDisable( GL_TEXTURE_2D );
    }
}

// -------------- glut-based demo code ---------------

#define GLUT_NO_BUTTON          -1

enum
{
    MENU_BACKGROUND,
    MENU_SUN,
    MENU_RANDOMFLARE,
    MENU_FILEFLARE
};

#define SUNWIDTH        50
#define SUNHEIGHT       HEIGHTFROMWIDTH(SUNWIDTH)

// Background enumeration -- what to show behind the flare.
enum
{
    BACK_TEXTURED,
    BACK_COLOUR0,
    BACK_COLOUR1,

    NBACK
};

#define FLARE_MINCOLOUR        MAKEID(140, 100, 50, 100)
#define FLARE_MAXCOLOUR        MAKEID(255, 255, 200, 255)
#define FLARE_MINELEMENTSPERFLARE         8
#define FLARE_MAXSIZE                   0.3f

/*
    Global variables
*/

int     xFlare = 150;
int     yFlare = 0;

FLARE_DEF       renderFlare;    // Flare to render.

Flare::Flare()
{
	SCREENwidth = glutGet( GLUT_WINDOW_WIDTH );
    SCREENheight = glutGet( GLUT_WINDOW_HEIGHT );

    //TM_loadTextures();

    FLARE_randomize(&renderFlare, NPIECETEXTURES, FLARE_RANGE(FLARE_MINELEMENTSPERFLARE, FLARE_MAXELEMENTSPERFLARE), FLARE_MAXSIZE, FLARE_MINCOLOUR, FLARE_MAXCOLOUR);
	


	surfRev.createCube();
	surfRev.addTexture(0, "flare/ring.png");
}

void Flare::FLARE_render(float cosine) {

    FLARE_DEF *flare = &renderFlare;
    
    
    int screen_w = glutGet(GLUT_WINDOW_WIDTH);
    int screen_h = glutGet(GLUT_WINDOW_HEIGHT);
    int cx = screen_w/2;
    int cy = screen_h/2;
	int lx = cx;
	int ly = cosine*cy;
    int     dx, dy;          // Screen coordinates of "destination"
    int     px, py;          // Screen coordinates of flare element
    int     maxflaredist, flaredist, flaremaxsize, flarescale;
    int     width, height, alpha;    // Piece parameters;
    int     i;
    FLARE_ELEMENT_DEF    *element;

    // Compute how far off-center the flare source is.
    maxflaredist = isqrt(cx*cx + cy*cy);
    flaredist = isqrt((lx - cx)*(lx - cx)+
                      (ly - cy)*(ly - cy));
    flaredist = (maxflaredist - flaredist);
    flaremaxsize = (int)(screen_w * flare->fMaxSize);
    flarescale = (int)(screen_w * flare->fScale);

    // Destination is opposite side of centre from source
    dx = cx + (cx - lx);
    dy = cy + (cy - ly);

    // Render each element.
    for (i = 0; i < flare->nPieces; ++i)
    {
        element = &flare->element[i];

        // Position is interpolated along line between start and destination.
        px = (int)((1.0f - element->fDistance)*lx + element->fDistance*dx);
        py = (int)((1.0f - element->fDistance)*ly + element->fDistance*dy);

        // Piece size are 0 to 1; flare size is proportion of
        // screen width; scale by flaredist/maxflaredist.
        width = (int)((flaredist*flarescale*element->fSize)/maxflaredist);

        // Width gets clamped, to allows the off-axis flares
        // to keep a good size without letting the elements get
        // too big when centered.
        if (width > flaremaxsize)
        {
            width = flaremaxsize;
        }

        // Flare elements are square (round) so height is just
        // width scaled by aspect ratio.
        height = HEIGHTFROMWIDTH(width);
        alpha = (flaredist*(element->argb >> 24))/maxflaredist;

        if ( width > 1 )
        {
            unsigned int    argb = (alpha << 24 ) | (element->argb & 0x00ffffff);

            drawQuad( px - width/2, py - height/2, width, height, element->texture, argb );
        }
    }
}


void Flare::FLARE_position(int x, int y) {
    xFlare = x;
    yFlare = y;
}

void Flare::FLARE_init() {

    SCREENwidth = glutGet( GLUT_WINDOW_WIDTH );
    SCREENheight = glutGet( GLUT_WINDOW_HEIGHT );

    TM_loadTextures();

    FLARE_randomize(&renderFlare, NPIECETEXTURES, FLARE_RANGE(FLARE_MINELEMENTSPERFLARE, FLARE_MAXELEMENTSPERFLARE), FLARE_MAXSIZE, FLARE_MINCOLOUR, FLARE_MAXCOLOUR);
}

