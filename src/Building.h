//
//  building.h
//  TheRobFordProject
//
//  Created by Grady Kestler on 12/2/13.
//  Copyright (c) 2013 Grady Kestler. All rights reserved.
//

#ifndef __TheRobFordProject__building__
#define __TheRobFordProject__building__
#include "SmartGLUT.h"
#include "Renderer.h"

class Building
{
private:
    int height;
    int vertBlock;
    int horiBlock;
    int parentBlock;
    GLuint texture;
    Vector3 boundingBox[8];
    
public:
    Building();
    Building(int, int, int, int);
    
    void assignTexture(GLuint, int, int, unsigned char*);
    int getParentBlock();
    void setPlacement(int, int);
    void drawBuilding();
    
};

#endif /* defined(__TheRobFordProject__building__) */
