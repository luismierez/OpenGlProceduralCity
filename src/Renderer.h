#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Matrix4.h"
#include "Camera.h"

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

