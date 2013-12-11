#include "Renderer.h"


using namespace std;
//--------------OSC-----------//
#if _DRAW_PD_
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
#endif


//----------End OSC---------//

static Camera camera;

int Renderer::width  = 512;   // set window width in pixels here
int Renderer::height = 512;   // set window height in pixels here
Tree* Renderer::currTree;

vector<Road> roads;
vector<Building> buildings;
vector<int> blocks;

static Matrix4 modelViewTemp;
static Matrix4 trackballMat;
static Matrix4 resultMatObj;
int track_x, track_y = 0;

std::vector<int> roadPlacementVert;
std::vector<int> roadPlacementHori;
std::vector<int> buildingBlocksToRender;
std::vector<int> plantBlocksToRender;

GLuint Renderer::texture[NUM_OF_TEXS];

void init()
{

    
    trackballMat.identity();
    resultMatObj.identity();

	#if DRAW_LSYS
	Renderer::currTree = new Tree();
	#endif

	#if DRAW_CITY
    //Randomly assign roadPlacement
    srand(time(NULL));
    int roadPlacement;

    Orientation orient;

    //Go through the number of roads
    for(int i=0; i<NUM_OF_ROADS; i++)
    {
        //Randomly place them
        roadPlacement = (NUM_OF_BLOCKS/2)-(rand()%(2*(NUM_OF_BLOCKS/2)));
//        roadPlacement = -1;
        
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
                    roadPlacement = (NUM_OF_BLOCKS/2)-(rand()%(2*(NUM_OF_BLOCKS/2)));
                    j=0;
                }
            }
            
            roadPlacementVert.push_back(roadPlacement);
        }
    
        //For all the odd roads, make them horizontal
        else
        {
            orient = horizontal;
            for(int j=0; j<roadPlacementHori.size(); j++)
            {
                while(abs(roadPlacement-roadPlacementHori[j]) <= 1)
                {
                    roadPlacement = (NUM_OF_BLOCKS/2)-(rand()%(2*(NUM_OF_BLOCKS/2)));
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
    
    
    //Assign each building to a block
    int buildingHeight = 20;
    int block = 0;
    
    int j=-(NUM_OF_BLOCKS/2)+1;
    
    int jStart=-(NUM_OF_BLOCKS/2)+1;
    int jEnd=-(NUM_OF_BLOCKS/2)+1;
    
    
    //Start at the farthest right, lowest block.
    while(j<=(NUM_OF_BLOCKS/2))
    {

        int i=-(NUM_OF_BLOCKS/2)+1;
        while(i<=(NUM_OF_BLOCKS/2))
        {

            //If there's a road
            if(std::find(roadPlacementHori.begin(), roadPlacementHori.end(), j) != roadPlacementHori.end() ||
               std::find(roadPlacementVert.begin(), roadPlacementVert.end(), i) != roadPlacementVert.end())
            {
                //If there's a vertical road, increment the block
                if(std::find(roadPlacementVert.begin(), roadPlacementVert.end(), i) != roadPlacementVert.end() &&
                   i!=-(NUM_OF_BLOCKS/2)+1)
                    block++;
                
                //If there's a horizontal road at the beginning of the grid
                if(j==-(NUM_OF_BLOCKS/2)+1 && std::find(roadPlacementHori.begin(), roadPlacementHori.end(), j) != roadPlacementHori.end())
                {
                    //Skip over it
                    jEnd++;
                    j=jEnd;
                    jStart=j;
                }
                else
                {
                    //Reset j and increment to the left
                    i++;
                    j=jStart;
                }

            }

            //If there's no road
            else
            {
                //Put a building
                buildingHeight=rand()%30+20;
                buildings.push_back(Building(buildingHeight, i, j, block));
                
                //If the block isn't in the list, add it
                if(std::find(blocks.begin(), blocks.end(), block) == blocks.end())
                {
                    blocks.push_back(block);
                }

                //If j isn't at the end of the grid
                if(j<(NUM_OF_BLOCKS/2))
                {
                    //Increment it
                    j++;
                    jEnd=j;
                }
                
                //If j is not at the end
                else{
                    //Reset j and incrememnt to the left
                    i++;
                    j=jStart;
                }
            }
            
        }
        if(std::find(roadPlacementVert.begin(), roadPlacementVert.end(), i-1) == roadPlacementVert.end())
           block++;
        jEnd++;
        j=jEnd;
        jStart=j;
    }
    
    int buildingBlockToRender=rand()%blocks.size();
    int numOfBuildingBlocks = rand()%(blocks.size()/2);
    numOfBuildingBlocks+=blocks.size()/2;
    for(int i=0; i<numOfBuildingBlocks; i++)
    {
        while(std::find(buildingBlocksToRender.begin(), buildingBlocksToRender.end(), buildingBlockToRender) != buildingBlocksToRender.end() &&
              buildingBlocksToRender.size()!=0)
        {
            buildingBlockToRender= rand()%blocks.size();
        }
        
        buildingBlocksToRender.push_back(buildingBlockToRender);
    }
    
    for (int i=0; i<blocks.size(); i++)
    {
        if(std::find(buildingBlocksToRender.begin(), buildingBlocksToRender.end(), i) != buildingBlocksToRender.end())
            plantBlocksToRender.push_back(i);
    }
    
    //Default view
	Vector4* e	= new Vector4(roadPlacementVert[0]*BLOCK_WIDTH-(BLOCK_WIDTH/2), 10, -(NUM_OF_BLOCKS/2)*BLOCK_WIDTH);
	Vector4* d	= new Vector4(roadPlacementVert[0]*BLOCK_WIDTH-(BLOCK_WIDTH/2), 0, 1);
	Vector4* up = new Vector4(0, 1, 0);
	camera = Camera(e, d, up);
    
    
    
    #else
    Vector4* e	= new Vector4(0, 100, -400);
	Vector4* d	= new Vector4(0, 0, 1);
	Vector4* up = new Vector4(0, 1, 0);
	camera = Camera(e, d, up);
    
	#endif

	#if DRAW_LSYS
	e	= new Vector4(0, 0, -100);
	d	= new Vector4(0, 0, 0);
	up = new Vector4(0, 1, 0);
	camera = Camera(e, d, up);
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
    for(int i=-(NUM_OF_BLOCKS/2); i<(NUM_OF_BLOCKS/2)+1; i++)
    {
        //Draw Vertical Lines
        glVertex3f(i*BLOCK_WIDTH, 0, BLOCK_WIDTH*(NUM_OF_BLOCKS/2));
        glVertex3f(i*BLOCK_WIDTH, 0, -BLOCK_WIDTH*(NUM_OF_BLOCKS/2));
        
        //Draw Horizontal Lines
        glVertex3f(BLOCK_WIDTH*(NUM_OF_BLOCKS/2), 0, i*BLOCK_WIDTH);
        glVertex3f(-BLOCK_WIDTH*(NUM_OF_BLOCKS/2), 0, i*BLOCK_WIDTH);
    }
    glEnd();
}

unsigned char* loadPPM(const char* filename, int& width, int& height)
{
	const int BUFSIZE = 128;
	FILE* fp;
	unsigned int read;
	unsigned char* rawData;
	char buf[3][BUFSIZE];
	char* retval_fgets;
	size_t retval_sscanf;
    
	if ( (fp=fopen(filename, "rb")) == NULL)
	{
		std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
		width = 0;
		height = 0;
		return NULL;
	}
    
	// Read magic number:
	retval_fgets = fgets(buf[0], BUFSIZE, fp);
    
	// Read width and height:
	do
	{
		retval_fgets=fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');
	retval_sscanf=sscanf(buf[0], "%s %s", buf[1], buf[2]);
	width  = atoi(buf[1]);
	height = atoi(buf[2]);
    
	// Read maxval:
	do
	{
        retval_fgets=fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');
    
	// Read image data:
	rawData = new unsigned char[width * height * 3];
	read = fread(rawData, width * height * 3, 1, fp);
	fclose(fp);
	if (read != 1)
	{
		std::cerr << "error parsing ppm file, incomplete data" << std::endl;
		delete[] rawData;
		width = 0;
		height = 0;
		return NULL;
	}
    
	return rawData;
}

// load image file into texture object
void loadTexture()
{
	GLuint *texturePtr = Renderer::texture;
    int buildWidth, buildHeight;   // texture width/height [pixels]
    unsigned char* buildData;
    
    int roadWidth, roadHeight;   // texture width/height [pixels]
    unsigned char* roadData;

	int barkWidth, barkHeight;   // texture width/height [pixels]
    unsigned char* barkData;

	int leavesWidth, leavesHeight;   // texture width/height [pixels]
    unsigned char* leavesData;
    
    // Load image file
    buildData = loadPPM("buildingWall.ppm", buildWidth, buildHeight);
    if (buildData==NULL) return;
    
    roadData = loadPPM("roadSection.ppm", roadWidth, roadHeight);
    if (roadData==NULL) return;

	barkData = loadPPM("treebark.ppm", barkWidth, barkHeight);
    if (buildData==NULL) return;
    
    leavesData = loadPPM("leaves.ppm", leavesWidth, leavesHeight);
    if (leavesData==NULL) return;
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // Create ID for texture
	glGenTextures(NUM_OF_TEXS, texturePtr);

    glBindTexture(GL_TEXTURE_2D, texturePtr[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, buildWidth, buildHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, buildData);

    
    glBindTexture(GL_TEXTURE_2D, texturePtr[1]);
    //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, roadWidth, roadHeight, GL_RGB, GL_UNSIGNED_BYTE, roadData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, roadWidth, roadHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, roadData);

	glBindTexture(GL_TEXTURE_2D, texturePtr[2]);
    //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, barkWidth, barkHeight, GL_RGB, GL_UNSIGNED_BYTE, barkData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, barkWidth, barkHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, barkData);

	glBindTexture(GL_TEXTURE_2D, texturePtr[3]);
    //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, leavesWidth, leavesHeight, GL_RGB, GL_UNSIGNED_BYTE, leavesData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, leavesWidth, leavesHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, leavesData);
}

void initGL()
{
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);   // enable smooth shading
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // black background
    glClearDepth(1.0f);        // depth buffer setup
    glEnable(GL_DEPTH_TEST);   // enables depth testing
    glDepthFunc(GL_LEQUAL);    // configure depth testing
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // really nice perspective calculations
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
    
	#if DRAW_LSYS
	currTree->draw();
	#endif

	#if DRAW_CITY
    //Draw a white city grid
//    glColor3f(1, 1, 1);
//    drawCityGrid();

    //Draw all roads
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    for(int i=0; i<roads.size(); i++)
    {
        roads[i].drawRoad();
    }
    
    //Draw Buildings
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    for(int i=0; i<buildings.size(); i++)
    {
        if(std::find(buildingBlocksToRender.begin(), buildingBlocksToRender.end(), buildings[i].getParentBlock()) != buildingBlocksToRender.end())
            buildings[i].drawBuilding();
    }

    //Draw all 3 of the Axis
//    drawAxis();
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
			Renderer::currTree->regenerate();
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
    glClearColor(1, 1, 1, 1.0);   	      // set clear color to black
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
    
    loadTexture();
    initGL();
    
    // Install callback functions:
    glutDisplayFunc(Renderer::displayCallback);
    glutReshapeFunc(Renderer::reshapeCallback);
    glutIdleFunc(Renderer::idleCallback);

    glutMouseFunc(mouse_func);
    glutMotionFunc(motion_func);
    glutKeyboardFunc(key_func);
    

    

	#if _DRAW_PD_
	_beginthread(runServer, 0, NULL);
	#endif
    glutMainLoop();
    return 0;
}

