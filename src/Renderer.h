#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Matrix4.h"

class Renderer
{
protected:
    Matrix4 matrix;                 // model matrix
    double angle;                   // rotation angle [degrees]
    
public:
    static int width, height;
    
    Renderer();   // Constructor
    Matrix4& getMatrix();
    
    static void idleCallback(void);
    static void reshapeCallback(int w, int h);
    static void displayCallback(void);
};

#endif

