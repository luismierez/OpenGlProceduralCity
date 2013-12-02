//
//  building.h
//  TheRobFordProject
//
//  Created by Grady Kestler on 12/2/13.
//  Copyright (c) 2013 Grady Kestler. All rights reserved.
//

#ifndef __TheRobFordProject__building__
#define __TheRobFordProject__building__

#include <iostream>
#include <GLUT/glut.h>

class Building
{
private:
    int height;
    int vertBlock;
    int horiBlock;
    
public:
    Building();
    Building(int, int, int);
    
    void setPlacement(int, int);
    void drawBuilding();
    
};

#endif /* defined(__TheRobFordProject__building__) */
