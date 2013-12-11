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
    roadPlacement = 0;
}
Road::Road(int placement)
{
    roadPlacement = placement;
}

void Road::setRoadPlacement(int placement)
{
    roadPlacement = placement;
}

void Road::setOrientation(Orientation inOrient)
{
    orientation = inOrient;
}

int Road::getOrientation()
{
    return orientation;
}

void Road::drawRoad()
{
    //gridSpot between -20 and 20
    glBegin(GL_QUADS);

    //Draw a road along the z axis with width of 10
    if(orientation==vertical){
        glNormal3f(0.0, 1.0, 0.0);
        for(int i=-NUM_OF_BLOCKS/2; i<NUM_OF_BLOCKS/2; i++)
        {
            glTexCoord2d(0, 0);
            glVertex3f(roadPlacement*BLOCK_WIDTH, 0, BLOCK_WIDTH*i); //bottom left
            glTexCoord2d(0, 1);
            glVertex3f(roadPlacement*BLOCK_WIDTH, 0, (BLOCK_WIDTH*i)+BLOCK_WIDTH); //top left
            glTexCoord2d(1, 1);
            glVertex3f(roadPlacement*BLOCK_WIDTH-BLOCK_WIDTH, 0, (BLOCK_WIDTH*i)+BLOCK_WIDTH); //top right
            glTexCoord2d(1, 0);
            glVertex3f(roadPlacement*BLOCK_WIDTH-BLOCK_WIDTH, 0, BLOCK_WIDTH*i); //bottom right
        }
    }
    
    //Draw a road along the x axis with width of 10
    else if(orientation==horizontal){
        glNormal3f(0, 1, 0);
        for(int i=-NUM_OF_BLOCKS/2; i<NUM_OF_BLOCKS/2; i++)
        {
            glTexCoord2d(0, 0);
            glVertex3f(BLOCK_WIDTH*i, 0, roadPlacement*BLOCK_WIDTH);
            glTexCoord2d(0, 1);
            glVertex3f((BLOCK_WIDTH*i)+BLOCK_WIDTH, 0, roadPlacement*BLOCK_WIDTH);
            glTexCoord2d(1, 1);
            glVertex3f((BLOCK_WIDTH*i)+BLOCK_WIDTH, 0, roadPlacement*BLOCK_WIDTH-BLOCK_WIDTH);
            glTexCoord2d(1, 0);
            glVertex3f(BLOCK_WIDTH*i, 0, roadPlacement*BLOCK_WIDTH-BLOCK_WIDTH);
        }
    }
    
    glEnd();
}

