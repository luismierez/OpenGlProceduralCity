//
//  building.cpp
//  TheRobFordProject
//
//  Created by Grady Kestler on 12/2/13.
//  Copyright (c) 2013 Grady Kestler. All rights reserved.
//

#include "Building.h"

Building::Building()
{
    height = 20;
}

Building::Building(int inHeight, int vert, int hori, int parent)
{
    height = inHeight;
    vertBlock = vert;
    horiBlock = hori;
    parentBlock = parent;
    
    boundingBox[0]=Vector3(vertBlock*BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH); //bottom left
    boundingBox[1]=Vector3(vertBlock*BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH); //top left
    boundingBox[2]=Vector3(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH); //top right
    boundingBox[3]=Vector3(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH); //bottom right
    
    boundingBox[4]=Vector3(vertBlock*BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    boundingBox[5]=Vector3(vertBlock*BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH);
    boundingBox[6]=Vector3(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH);
    boundingBox[7]=Vector3(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    
    /*Bottom Face = 0,1,2,3
      Left Face = 0,1,5,4
      Right Face = 3,2,6,7
      Back Face = 2,1,5,6
      Front Face = 3,0,4,7
      Top Face = 4,5,6,7
     */
}

int Building::getParentBlock()
{
    return parentBlock;
}


void Building::drawBuilding()
{
    glBegin(GL_QUADS);
    //Bottom Face
    glColor3f(1, 1, 1);
    glNormal3f(0, -1, 0);
    glVertex3f(vertBlock*BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH); //bottom left
    glVertex3f(vertBlock*BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH); //top left
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH); //top right
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH); //bottom right
    
    //Left Face
    glNormal3f(1, 0, 0);
    glTexCoord2d(1, 1);
    glVertex3f(vertBlock*BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    glTexCoord2d(0, 1);
    glVertex3f(vertBlock*BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH);
    glTexCoord2d(0, 0);
    glVertex3f(vertBlock*BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH);
    glTexCoord2d(1, 0);
    glVertex3f(vertBlock*BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    
    //Right Face
    glNormal3f(-1, 0, 0);
    glTexCoord2d(1, 1);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    glTexCoord2d(0, 1);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH);
    glTexCoord2d(0, 0);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH);
    glTexCoord2d(1, 0);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    
    //Back Face
    glNormal3f(0, 0, 1);
    glTexCoord2d(1, 1);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH);
    glTexCoord2d(0, 1);
    glVertex3f(vertBlock*BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH);
    glTexCoord2d(0, 0);
    glVertex3f(vertBlock*BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH);
    glTexCoord2d(1, 0);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH);

    
    //Front Face
    glNormal3f(0, 0, -1);
    glTexCoord2d(1, 1);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    glTexCoord2d(0, 1);
    glVertex3f(vertBlock*BLOCK_WIDTH, 0, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    glTexCoord2d(0, 0);
    glVertex3f(vertBlock*BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    glTexCoord2d(1, 0);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    
    //Top Face
    glNormal3f(0, 1, 0);
    glVertex3f(vertBlock*BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH);
    glVertex3f(vertBlock*BLOCK_WIDTH-BLOCK_WIDTH, height, horiBlock*BLOCK_WIDTH-BLOCK_WIDTH);
    
    glEnd();

}