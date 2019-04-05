#include <stdio.h>     // - Just for some ASCII messages
#include <cstring>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
#include <time.h>

#include "gl/glut.h"   // - An interface and windows management library
#include "visuals.h"   // Header file for our OpenGL functions

#define NUM_OF_STARS 500

model md;
static float tx = 0.0;
static float ty = 0.0;
static float tz = 0.0;
static float rx = 0.0;
static float ry = 0.0;
static float rz = 0.0;
static float rotx = 0.0;
static bool animate = false;
static float red = 1.0;
static float green = 0.0;
static float blue = 0.0;
clock_t begin_time = clock();
static int starsNum = 0;
static int starsPos[NUM_OF_STARS][3];
extern int width;
extern int height;
static float value = 0.0;
static int flag = 0;

using namespace std;

void axes()
{
	glColor3f(0.6, 0.6, 0.6);
	glPushMatrix();
	glTranslatef(0, 0, -1.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(100.0, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 100.0);
	glEnd();
	glPopMatrix();
}

void keimeno(const char *str,float size)
{

	glPushMatrix();
	glScalef(size,size,size);

	for(int i = 0; i < strlen(str); i++)
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
	glPopMatrix();

}


void Render()
{    
  //CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
													   // and the depth buffer
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();
  
  glTranslatef(0, 0, -100);
  for (int i = 0; i < starsNum; ++i)
  {
	  glPushMatrix();
	  glTranslatef(starsPos[i][0], starsPos[i][1], starsPos[i][2]);
	  glColor3f(1.0, 1.0, 1.0);                           // Set drawing colour
	  glutSolidSphere(0.1,  50, 50);

	  glPopMatrix();
  }

  //Transactions for every shape
  glRotatef(rx, 1, 0, 0);
  glRotatef(ry, 0, 1, 0);
  glRotatef(rz, 0, 0, 1);
  glTranslatef(tx, ty, tz);

	

  //SUN CREATION. 
  glColor3f(1.0, 1.0, 0.0);
  glutSolidSphere(20, 1000, 100);

  
  //Create Axes for Sun
  axes();
  
  //(01)             
  

  //(02)
  //glColor3f(0.8, 0.1, 0.1);
  //glTranslatef(-20.0,0.0,0.0);
  //keimeno("Dokimastiko keimeno",0.05f);

  //(03)             
  
  
  glPushMatrix();
  //EARTH CREATION. boom
  glRotatef(rotx, 0, -1, 0);
  glTranslatef(50, 0.0, 0.0);
  glColor3f(0.0, 0.0, 1.0);                           // Set drawing colour
  //glutSolidSphere(10, 50, 50);
  glScalef(0.017, 0.017, 0.017);
  DisplayModel(md);
  glPopMatrix();

  glPushMatrix();
  //MOON CREATION
  glRotatef(rotx, 0, -1, 0);	//Earth's rotation
  glTranslatef(50, 0.0, 0.0);

  glRotatef(rotx * 4, 1, 0, 0);
  glTranslatef(0, 20.0, 0.0);
  glColor3f(0.5, 0.5, 0.5);                           // Set drawing colour
  //glutSolidSphere(2, 50, 50);
  glScalef(0.005, 0.005, 0.005);
  DisplayModel(md);

  glPopMatrix();
  
  //Second sun for invisibility
  glColor4f(1.0, 1.0, 0.0, value);
  glutSolidSphere(30, 1000, 100);

  
 
  glutSwapBuffers();             // All drawing commands applied to the 
                                 // hidden buffer, so now, bring forward
                                 // the hidden buffer and hide the visible one
}


//-----------------------------------------------------------

void Resize(int w, int h)
{ 
  // define the visible area of the window ( in pixels )
  if (h==0) h=1;
  glViewport(0,0,w,h); 

  // Setup viewing volume

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
 
  gluPerspective(60.0, ((float)w/(float)h), 1.0, 500.0);

}

void Idle()
{
	if (animate)
	{
		rotx += 0.5;
		if (value > 1.0)
			flag = 1;
		else if (value < 0.0)
			flag = 0;
		if (flag == 0)
			value += 0.01;
		else
			value -= 0.01;
	}
	glutPostRedisplay();
}

void Keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
	case  27 : exit(0);
		break;
	case  'q': exit(0);
		break;
	case 's' : tz-=0.5f;
		break;
	case 'w' : tz+=0.5f;
		break;
	case 'h': rx -= 1;
		break;
	case 'b': rx += 1;
		break;
	case 'j': ry -= 1;
		break;
	case 'n': ry += 1;
		break;
	case 'k': rz -= 1;
		break;
	case 'm': rz += 1;
		break;
	case 'p': 
		animate = !animate;
		glutPostRedisplay();
		break;
	default : break;
	}

	glutPostRedisplay();

}

void Special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT : tx -= 0.5f;
		break;
	case GLUT_KEY_RIGHT: tx += 0.5f;
		break;
	case GLUT_KEY_DOWN: ty -= 0.5f;
		break;
	case GLUT_KEY_UP: ty += 0.5f;
		break;
	default: break;
	}

	glutPostRedisplay();

}

void Mouse(int button,int state,int x,int y)
{
	 if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	 {
		 animate = !animate;
         glutPostRedisplay();
	 }
}


void Setup()  // TOUCH IT !! 
{ 
	md.faces = 0;
	md.points = 0;
	ReadFile(&md);

	//Parameter handling
	glShadeModel (GL_SMOOTH);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);

	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
  
	//Set up light source
	GLfloat light_position[] = { 0.0, 0.0, 0.000000000000000001, 0.0 };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position);

	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

	   
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
	

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	//01
	glFrontFace(GL_CCW);

 

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);

	//Stars
	starsNum = (rand() % (NUM_OF_STARS/2+1)) + NUM_OF_STARS / 2;
	for (int i = 0; i < starsNum; ++i)
	{
		starsPos[i][0] = rand() % width - width/2;
		starsPos[i][1] = rand() % height - height/2;
		starsPos[i][2] = rand() % 300 + 1;
		starsPos[i][0] /= 4;
		starsPos[i][1] /= 4;
	}
}

void MenuSelect(int choice)
{
	switch (choice) {
		case RED : 
			red = 1.0; 
			green = 0.0; 
			blue = 0.0; break;
		case GREEN : 
			red = 0.0; 
			green = 1.0; 
			blue = 0.0; break;
		case BLUE : 
			red = 0.0; 
			green = 0.0; 
			blue = 1.0; break;
		case WHITE : 
			red = 1.0; 
			green = 1.0; 
			blue = 1.0; break;
	}

}

void ReadFile(model *md)
{
	char trash[256];
	int trashnumber;
	ifstream obj_file("planet.obj");                   // Open the file for reading OBJINFO.TXT
   
	if (obj_file.fail()) 
		exit(1);

	char firstLetter;
	while (1)
	{
		if (obj_file.eof())
			break;
		obj_file >> firstLetter;
		if (firstLetter == 'v')
		{
			firstLetter = obj_file.peek();
			if (firstLetter == 'n')	//CASE: -vn
			{
				obj_file.getline(trash, 256);
			}
			else					//CASE -v
			{
				obj_file >> md->obj_points[md->points].x;
				obj_file >> md->obj_points[md->points].y;
				obj_file >> md->obj_points[md->points].z;
				md->points++;
			}

		}
		else if (firstLetter == 'f')
		{
			for (int i = 0; i < 3; i++)
			{
				obj_file >> md->obj_faces[md->faces].vtx[i];
				obj_file >> firstLetter;		//Trash letters for '/'
				obj_file >> firstLetter;
				obj_file >> trashnumber;
			}
			md->faces++;
		}
		else
		{
			obj_file.getline(trash, 256);
		}
	}
   obj_file.close();
}

void DisplayModel(model md)
{

	glPushMatrix();
	glBegin(GL_TRIANGLES);
	
	for (int i = 0; i < md.faces; i++)
	{
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[0]-1].x,md.obj_points[md.obj_faces[i].vtx[0]-1].y,md.obj_points[md.obj_faces[i].vtx[0]-1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[1]-1].x,md.obj_points[md.obj_faces[i].vtx[1]-1].y,md.obj_points[md.obj_faces[i].vtx[1]-1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[2]-1].x,md.obj_points[md.obj_faces[i].vtx[2]-1].y,md.obj_points[md.obj_faces[i].vtx[2]-1].z);
	}
	
	glEnd();
	glPopMatrix();

}