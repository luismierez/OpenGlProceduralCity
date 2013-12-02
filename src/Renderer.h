#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Matrix4.h"
#include "Camera.h"

#ifdef _APPLE_
#include <GLUT/glut.h>
#endif

#ifdef _WIN32_
#include <Gl/glut.h>
#endif

#define DRAW_CITY 1
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

