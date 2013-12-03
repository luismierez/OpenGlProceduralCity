//
//  building.cpp
//  TheRobFordProject
//
//  Created by Grady Kestler on 12/2/13.
//  Copyright (c) 2013 Grady Kestler. All rights reserved.
//

#include "Building.h"
#include "Renderer.h"


Building::Building()
{
    height = 20;
}

Building::Building(int inHeight, int vert, int hori)
{
    height = inHeight;
    vertBlock = vert;
    horiBlock = hori;
}

void Building::setPlacement(int vert, int hori)
{
    vertBlock = vert;
    horiBlock = hori;
}

void Building::drawBuilding()
{
    glBegin(GL_QUADS);
    //Bottom Face
    glColor3f(.7, .3, .9);
    glNormal3f(0, -1, 0);
    glVertex3f(vertBlock*BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    
    //Left Face
    glNormal3f(-1, 0, 0);
    glVertex3f(vertBlock*BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    
    //Right Face
    glNormal3f(1, 0, 0);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    
    //Front Face
    glNormal3f(0, 0, 1);
    glVertex3f(vertBlock*BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH);
    
    //Front Face
    glNormal3f(0, 0, -1);
    glVertex3f(vertBlock*BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    
    //Top Face
    glNormal3f(0, 1, 0);
    glVertex3f(vertBlock*BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    
    glEnd();

}