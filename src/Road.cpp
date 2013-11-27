//
//  Road.cpp
//  TheRobFordProject
//
//  Created by Grady Kestler on 11/26/13.
//  Copyright (c) 2013 Grady Kestler. All rights reserved.
//

#include "Road.h"

Road::Road()
{
    width = 10;
}

void Road::setOrientation(Orientation inOrient)
{
    orientation = inOrient;
};

int Road::getOrientation()
{
    return orientation;
};

void Road::drawRoad()
{
    glBegin(GL_QUADS);
    
    //Draw a road along the z axis with width of 10
    if(orientation==vertical){
        glVertex3f(10.0, 0, -200);
        glVertex3f(10.0, 0, 200);
        glVertex3f(0.0, 0, 200);
        glVertex3f(0.0, 0, -200);

    }
    
    //Draw a road along the x axis with width of 10
    else if(orientation==horizontal){
        glNormal3f(0, 1, 1);
        glVertex3f(-200, 0, 10.0);
        glVertex3f(200, 0, 10.0);
        glVertex3f(200, 0, 0.0);
        glVertex3f(-200, 0, 0.0);
    }
    
    glEnd();
};

