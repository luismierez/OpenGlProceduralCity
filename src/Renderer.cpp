#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <process.h>
#include <algorithm>

#include "Renderer.h"
#include "Matrix4.h"
#include "Road.h"
#include "Building.h"
#include "Tree.h"

using namespace std;
//--------------OSC-----------//
#include "oscpkt.hh"
#include "udp.hh"

using std::cout;
using std::cerr;

using namespace oscpkt;
const int PORT_NUM = 9109;
float red = 0;
float green = 0;
float blue = 0;

void runServer(void *param)
{
	UdpSocket sock;
	sock.bindTo(PORT_NUM);
	if(!sock.isOk())
	{
		cerr << "Error opening port " << PORT_NUM << ": " << sock.errorMessage() << "\n";
	} else 
	{
		cout << "Server started, will listen to packets on port " << PORT_NUM << std::endl;
		PacketReader pr;
		PacketWriter pw;
		while(sock.isOk())
		{
			if (sock.receiveNextPacket(30)) // timeout in ms
			{
				pr.init(sock.packetData(), sock.packetSize());
				oscpkt::Message *msg;
				while(pr.isOk() && (msg = pr.popMessage()) != 0)
				{
					int iarg;
					double darg;
					float farg;
					if(msg->match("/red").popFloat(farg).isOkNoMoreArgs())
					{
						red = farg;
					}
					if (msg->match("/green").popFloat(farg).isOkNoMoreArgs())
					{
						green = farg;
					}

					if (msg->match("/blue").popFloat(farg).isOkNoMoreArgs())
					{
						blue = farg;
					}
					cout << "Red: " << red << "\n";
					cout << "Green: " << green << "\n";
					cout << "Blue: " << blue << "\n";
				}


			}
		}
	}
}


//----------End OSC---------//

static Camera camera;

int Renderer::width  = 512;   // set window width in pixels here
int Renderer::height = 512;   // set window height in pixels here

vector<Road> roads;
vector<Building> buildings;

static Matrix4 modelViewTemp;
static Matrix4 trackballMat;
static Matrix4 resultMatObj;
int track_x, track_y = 0;

std::vector<int> roadPlacementVert;
std::vector<int> roadPlacementHori;

void init()
{
    //Default view
	Vector4* e	= new Vector4(0, 10, 10);
	Vector4* d	= new Vector4(0, 0, -1);
	Vector4* up = new Vector4(0, 1, 0, 0);
	camera = Camera(e, d, up);
    
    trackballMat.identity();
    resultMatObj.identity();

	#if DRAW_CITY
    //Randomly assign roadPlacement
    srand(time(NULL));
    int roadPlacement;

    Orientation orient;
    
    //Go through the number of roads
    for(int i=0; i<NUM_OF_ROADS; i++)
    {
        //Randomly place them
        roadPlacement = NUM_OF_BLOCKS-(rand()%(2*NUM_OF_BLOCKS+1));
        
        //For all the even roads
        if(i%2 == 0){
            //make them vertical (along the z-axis)
            orient = vertical;
            
            //compare them against the past road placements
            for(int j=0; j<roadPlacementVert.size(); j++)
            {
                //If they're directly next to eachother, reassign the current road placement
                while(abs(roadPlacement-roadPlacementVert[j]) <= 1)
                {
                    roadPlacement = NUM_OF_BLOCKS-(rand()%(2*NUM_OF_BLOCKS+1));
                    j=0;
                }
            }
            
            roadPlacementVert.push_back(roadPlacement);
            printf("%d\n", roadPlacement);
        }
    
        //For all the odd roads, make them horizontal
        else
        {
            orient = horizontal;
            for(int j=0; j<roadPlacementHori.size(); j++)
            {
                while(abs(roadPlacement-roadPlacementHori[j]) <= 1)
                {
                    roadPlacement = NUM_OF_BLOCKS-(rand()%(2*NUM_OF_BLOCKS+1));
                    j=0;
                }
            }
            
            roadPlacementHori.push_back(roadPlacement);
        }
        
        //Add the road to the list of roads
        roads.push_back(Road(roadPlacement));
        
        //Set the current roads orientation
        roads[i].setOrientation(orient);
    }
    
    
    
    int buildingHeight;
    for(int i=-NUM_OF_BLOCKS+1; i<NUM_OF_BLOCKS+1; i++)
    {
        for(int j=-NUM_OF_BLOCKS+1; j<NUM_OF_BLOCKS+1; j++)
        {
            //Checks all of the road placements
            if(std::find(roadPlacementVert.begin(), roadPlacementVert.end(), i) == roadPlacementVert.end() &&
               std::find(roadPlacementHori.begin(), roadPlacementHori.end(), j) == roadPlacementHori.end())
            {
                buildingHeight = rand()%30+20;
                buildings.push_back(Building(buildingHeight, i, j));
            }
        }
    }
	#endif

}

void drawAxis()
{
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(-Renderer::width, 0, 0);
    glVertex3f(Renderer::width, 0, 0);
    
    glColor3f(0, 1, 0);
    glVertex3f(0, -Renderer::height, 0);
    glVertex3f(0, Renderer::height, 0);
    
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -100);
    glVertex3f(0, 0, 100);
    glEnd();
    
}

void drawCityGrid()
{
    glBegin(GL_LINES);
    for(int i=-NUM_OF_BLOCKS; i<NUM_OF_BLOCKS+1; i++)
    {
        //Draw Vertical Lines
        glVertex3f(i*BLOCK_WIDTH, 0, BLOCK_WIDTH*NUM_OF_BLOCKS);
        glVertex3f(i*BLOCK_WIDTH, 0, -BLOCK_WIDTH*NUM_OF_BLOCKS);
        
        //Draw Horizontal Lines
        glVertex3f(BLOCK_WIDTH*NUM_OF_BLOCKS, 0, i*BLOCK_WIDTH);
        glVertex3f(-BLOCK_WIDTH*NUM_OF_BLOCKS, 0, i*BLOCK_WIDTH);
    }
    glEnd();
    
    
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Renderer::idleCallback(void)
{
    displayCallback();  // call display routine to re-draw renderer
}

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void Renderer::reshapeCallback(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, w, h);  // set new viewport size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
    glTranslatef(0, 0, -100);
    glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
void Renderer::displayCallback(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);
    
    modelViewTemp.identity();
    
    modelViewTemp = modelViewTemp.multiply(*camera.getCameraMatrixInverse());
    modelViewTemp = modelViewTemp.multiply(resultMatObj);
    
    glLoadMatrixd(modelViewTemp.getPointer());
    glNormal3f(0.0, 1.0, 0.0);
	
	#if DRAW_CITY
    //Draw a white city grid
    glColor3f(1, 1, 1);
    drawCityGrid();

    //Draw all roads
    for(int i=0; i<roads.size(); i++)
    {
        roads[i].drawRoad();
    }
    
    //Draw Buildings
    for(int i=0; i<buildings.size(); i++)
    {
        buildings[i].drawBuilding();
    }

    //Draw all 3 of the Axis
    drawAxis();
	#endif

    glFlush();
    glutSwapBuffers();

}
void mouse_func (int button, int state, int x, int y)
{
    
    switch (button) {
        case GLUT_LEFT_BUTTON:
            track_x=x;
            track_y=y;
            break;
        default:
            break;
    }
}


void motion_func (int x, int y)
{
    if(track_x!=x && track_y!=y)
    {
        trackballMat = modelViewTemp.trackballRotation(Renderer::width, Renderer::height, track_x, track_y, x, y);
        resultMatObj = resultMatObj.multiply(trackballMat);
        track_x=x;
        track_y=y;
    }
}

void key_func(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 't':
			Tree tree = Tree();
			cout << tree.generateTree("s") << "\n";
			break;
	}
}

int main(int argc, char *argv[])
{
    init();

    float specular[]  = {1.0, 1.0, 1.0, 1.0};
    float shininess[] = {100.0};
    float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
    
    glutInit(&argc, argv);      	      	      // initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
    glutInitWindowSize(Renderer::width, Renderer::height);      // set initial window size
    glutCreateWindow("The Rob Ford Project");    	      // open window and set window title
    
    glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
    glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
    glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
    glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
    glShadeModel(GL_SMOOTH);             	      // set shading to smooth
    glMatrixMode(GL_PROJECTION);
    
    // Generate material properties:
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    
    // Generate light source:
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    // Install callback functions:
    glutDisplayFunc(Renderer::displayCallback);
    glutReshapeFunc(Renderer::reshapeCallback);
    glutIdleFunc(Renderer::idleCallback);

    glutMouseFunc(mouse_func);
    glutMotionFunc(motion_func);
	glutKeyboardFunc(key_func);
    

	#if DRAW_PD
	_beginthread(runServer, 0, NULL);
	#endif
    glutMainLoop();
    return 0;
}

