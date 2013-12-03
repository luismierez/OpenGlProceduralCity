#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Matrix4.h"
#include "Camera.h"
#include "SmartGLUT.h"

/* Development Macros: Enable or disable certain parts of the program */
#define DRAW_CITY 0 /* Grady's City Generation Test */
#define DRAW_PD 0	/* Luis's PD/UDP tests */
#define DRAW_LSYS 0 /* Ryan's L-System Tree Test */
/* End dev marcos */

#define NUM_OF_ROADS 10
#define NUM_OF_BLOCKS 10
#define BLOCK_WIDTH 10

class Renderer
{
public:
    static int width, height;
    
    Renderer();   // Constructor
    Matrix4& getMatrix();
    
    static void idleCallback(void);
    static void reshapeCallback(int w, int h);
    static void displayCallback(void);
};

#endif

