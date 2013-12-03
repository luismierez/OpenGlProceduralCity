//
//  Road.h
//  TheRobFordProject
//
//  Created by Grady Kestler on 11/26/13.
//  Copyright (c) 2013 Grady Kestler. All rights reserved.
//

#ifndef __TheRobFordProject__Road__
#define __TheRobFordProject__Road__

#include "SmartGLUT.h"

enum Orientation
{
    vertical = 0,
    horizontal
};

class Road
{
private:
    int width;
    int orientation;
    int roadPlacement;

public:
    Road();
    
    Road(int);
    void setRoadPlacement(int);
    void setOrientation(Orientation);
    int getOrientation();
    void drawRoad();
};

#endif /* defined(__TheRobFordProject__Road__) */
