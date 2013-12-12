#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

#include "Matrix4.h"
#include "Camera.h"
#include "SmartGLUT.h"
#include "Road.h"
#include "Building.h"
#include "Tree.h"
#include "Particles.h"

/* Development Macros: Enable or disable certain parts of the program */
#define DRAW_CITY 0 /* Grady's City Generation Test */
#define DRAW_PD 0	/* Luis's PD/UDP tests */
#define DRAW_LSYS 1 /* Ryan's L-System Tree Test */
#define DRAW_PARTICLES 1
/* End dev marcos */

//NUM_OF_ROADS must be less than half the number of blocks
#define NUM_OF_ROADS 10
#define NUM_OF_BLOCKS 20
#define BLOCK_WIDTH 30
#define NUM_OF_TEXS 4
#define TEX_HEIGHT 768
#define TEX_WIDTH 768
#define TEST_TRESS_TO_GEN 100

class Renderer
{
public:
    static int width, height;
	static vector<Tree> trees;
//    static GLuint texture[2];
    
    Renderer();   // Constructor
    Matrix4& getMatrix();
    
    static void idleCallback(void);
    static void reshapeCallback(int w, int h);
    static void displayCallback(void);
	static GLuint texture[NUM_OF_TEXS];
};

#endif

