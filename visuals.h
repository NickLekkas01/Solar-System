#define RED 1
#define GREEN 2
#define BLUE 3
#define WHITE 4

struct point 
{
	GLfloat x; 
	GLfloat y; 
	GLfloat z; 
};

struct face
{
	int vtx[3];
};

struct model
{
	point obj_points[10000];
	face obj_faces[20000];
	int points;
	int faces;
};


//-------- Functions --------------------------------

void Render();
// The function responsible for drawing everything in the 
// OpenGL context associated to a window. 

void Resize(int w, int h);
// Handle the window size changes and define the world coordinate 
// system and projection type

void Setup();
// Set up the OpenGL state machine and create a light source

void Idle();

void ReadFile(model*);
//Function for reading a model file

void DisplayModel(model);
// Function for displaying a model

void Keyboard(unsigned char key,int x,int y);
// Function for handling keyboard events.

void Special(int key, int x, int y);

void Mouse(int button,int state,int x,int y); 
// Function for handling mouse events

void MenuSelect(int choice);

