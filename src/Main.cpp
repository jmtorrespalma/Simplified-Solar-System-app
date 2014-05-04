//**************************************************************************
// SSSA
//
// Juan Manuel Torres Palma 
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "vertex.h"
#include "ObjetoGrafico.h"
#include "ObjetoRevolucionText.h"
#include "file_ply_stl.h"
#include "SolarSystem.h"
#include "jpg_imagen.hpp"



// Axis size
const int AXIS_SIZE=5000;

//enum used as interface to switch between options with keys and pop-up menus.
enum MyType{POINTS, LINES, SOLID, CHESS, LIGHTS, TEXTURES, QUIT, MOV, NONE};
MyType dibujar = NONE;

//Menus id variables.
int main_menu, draw_mode_menu;


//Used to move light 0
float angy_luz = 0.0;

//Flag for activating lighting and textures.
bool interruptor = false; //Lighting switch
bool interruptor2 = false; //Texture switch
bool animation_switch = false; //Animation switch

//Drawn object.
SolarSystem ss;

//Textures id's, we'll use 4 different textures.
GLuint idTex[4] ;

//Define camera position in polar coordinate system.
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

//Variables used to control the window size and perspectives transformation
GLfloat Window_width,Window_height,Front_plane,Back_plane;

//Window size and position variables
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
// Clearing window function.
//***************************************************************************

void clear_window(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


void Quit(){
	glutDestroyMenu(draw_mode_menu); //Destroys pop-up menus
	glutDestroyMenu(main_menu); 
	exit(0);
}

//**************************************************************************
// Function to define proyection transformation
//***************************************************************************

void change_projection(){

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);

}

//**************************************************************************
// Function to emplace the camera.
//***************************************************************************

void change_observer(){

	//Observer position
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-Observer_distance);
	glRotatef(Observer_angle_x,1,0,0);
	glRotatef(Observer_angle_y,0,1,0);

}

//**************************************************************************
// Function to draw axis
//***************************************************************************

void draw_axis(){

	glBegin(GL_LINES);

	//Red for X axis
	glColor3f(1,0,0);
	glVertex3f(-AXIS_SIZE,0,0);
	glVertex3f(AXIS_SIZE,0,0);

	//Green for Y axis
	glColor3f(0,1,0);
	glVertex3f(0,-AXIS_SIZE,0);
	glVertex3f(0,AXIS_SIZE,0);

	//Blue for Z axis
	glColor3f(0,0,1);
	glVertex3f(0,0,-AXIS_SIZE);
	glVertex3f(0,0,AXIS_SIZE);

	glEnd();
}


//**************************************************************************
// Function to draw any object, in our case, our Solar System
//***************************************************************************

void draw_objects()
{
    	switch (dibujar){
		
		case POINTS:
			glPointSize(3.0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);		
			ss.Draw(idTex);
			break;

		case LINES:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			ss.Draw(idTex);
			break;

		case SOLID:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			ss.Draw(idTex);
			break;

		case CHESS:
			break;			

	}

}

//**************************************************************************
// Function to emplace lights. 
//***************************************************************************


void ColocarLuz(){
	GLfloat pos_luz0[4] = {0.0, 0.0, 1.0, 0.0}; //Light0 position.
	GLfloat pos_luz1[4] = {0.0, 0.0, 0.0, 1.0}; //Light1 position is 
	GLfloat col_luz0[4] = {1.0, 1.0, 1.0, 1};
	GLfloat diffuse[4] = {1.0, 1.0, 1.0, 1.0};
	GLfloat zero[4] = {0.0, 0.0, 0.0, 1.0};
	
	glEnable(GL_NORMALIZE); //Used to avoid resized or scalated objects to have less light.
	
	glPushMatrix(); //Used to rotate Light0

	glRotatef(angy_luz, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, pos_luz0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, col_luz0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, zero);

	glPopMatrix();

	glPushMatrix();
	glLightfv(GL_LIGHT1, GL_POSITION, pos_luz1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, col_luz0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glPopMatrix();

	glShadeModel(GL_SMOOTH);
}



//**************************************************************************
//
//***************************************************************************

void draw_scene(void){
	clear_window();
	change_observer();
	ColocarLuz();
	draw_axis();
	draw_objects();
	glutSwapBuffers();
}



//***************************************************************************
// This function is called when a window resizing event occurs
//***************************************************************************

void change_window_size(int Ancho1,int Alto1){
	change_projection();
	glViewport(0,0,Ancho1,Alto1);

	glutPostRedisplay();
}


//***************************************************************************
//Callback functions for menu options
//***************************************************************************
void MenuInterface(int option){
	switch(option){
		case MOV:
			animation_switch = !animation_switch;
			break;
		case QUIT:
			Quit(); //Throws a warning when call it, cause tries to delete menu while in use.
			break;
		
	}
	
	glutPostRedisplay();

}

void DrawingModeInterface(int option){

	if (option <= CHESS) //In this case, its a visualization change.
		dibujar = (MyType) option;
	else{
		if (option == LIGHTS){
			interruptor = !interruptor;
			if (interruptor){
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
				glEnable(GL_LIGHT1);
			}
			else
				glDisable(GL_LIGHTING);
		}
		
		else{ //Can only be textures.
			interruptor2 = !interruptor2;
			if (interruptor2)
				glEnable(GL_TEXTURE_2D);
			else
				glDisable(GL_TEXTURE_2D);
		}		

	}
	glutPostRedisplay();
}


//***************************************************************************
// Function called when a normal key event occurs (Normal key is pressed)
//***************************************************************************
void normal_keys(unsigned char Tecla1,int x,int y) // Key, mouse x position and mouse y position
{
	switch(toupper(Tecla1)){
		case 'Q':
			Quit();
			break;
		case 'V': //Draw points
			dibujar = POINTS;
			break;
		case 'L': //Draw lines.
			dibujar = LINES;
			break;
		case 'S': //Dibujo solid,
			dibujar = SOLID;
			break;
		case 'A':
			dibujar = CHESS;
			break;
		case 'O': //Manually animates our scene.
			ss.IncreaseAngles();
			break;

		case 'B': //Move Light0 clockwise
			angy_luz += 1.0;
			break;
		case 'N': //Move Light0 counter clockwise
			angy_luz -= 1.0;
			break;
		case '5': //Enable textures
			interruptor2 = !interruptor2;
			if (interruptor2)
				glEnable(GL_TEXTURE_2D);
			else
				glDisable(GL_TEXTURE_2D);
			
			break;

		case '4': //Enable lighting
			interruptor = !interruptor;
			if (interruptor){
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
				glEnable(GL_LIGHT1);
			}
			else
				glDisable(GL_LIGHTING);
			break;
		case 'T':
			animation_switch = !animation_switch;
			break;
	}

	
	glutPostRedisplay();
}

//***************************************************************************
// Function called when a special key is pressed.
//***************************************************************************

void special_keys(int Tecla1,int x,int y){//Same than normal keys arguments.

	switch (Tecla1){
		case GLUT_KEY_LEFT:Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;break;
		case GLUT_KEY_UP:Observer_angle_x--;break;
		case GLUT_KEY_DOWN:Observer_angle_x++;break;
		case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
		case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}

	glutPostRedisplay();

}




void Animate(){

	if (animation_switch){
		
		ss.IncreaseAngles();
		glutPostRedisplay();
	}
}



//*************************************************************************************
//Intialization function: window, observer, camera, z-buffer, textures and pop-up menus
//*************************************************************************************

void initialize(void){
	//Window and planes are initialized
	Window_width=.5;
	Window_height=.5;
	Front_plane=1;
	Back_plane=1000;

	//Observer is placed in z axis.
	Observer_distance=3*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

	//Select clean screen colour
	glClearColor(1,1,1,1);

	//Enable Z-Buffer.
	glEnable(GL_DEPTH_TEST);
	change_projection();
	glViewport(0,0,UI_window_width,UI_window_height);


	//Reading of textures.
	glGenTextures(4, idTex );

	vector<string> texture_files;
	texture_files.push_back("Textures/sun_texture.jpg");
	texture_files.push_back("Textures/earth_texture.jpg");
	texture_files.push_back("Textures/moon_texture.jpg");
	texture_files.push_back("Textures/space_texture.jpg");

	jpg::Imagen * pimg = NULL ; //Jpeg image pointer.


	for (int i = 0; i < 4; ++i){

		glBindTexture( GL_TEXTURE_2D, idTex[i] );

		// Load the dessired image
		pimg = new jpg::Imagen(texture_files.at(i));

		int depth = GL_RGB; // intern format RGB
		int width = pimg->tamX(); // number of columns (unsigned)
		int height = pimg->tamY(); // number of rows (unsigned)
		void* data = pimg->leerPixels(); // pointer to data(unsigned char *)

		gluBuild2DMipmaps(GL_TEXTURE_2D, depth, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  
		delete pimg;
		glBindTexture( GL_TEXTURE_2D, idTex[i] );
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); //What to do when s texture is out of range.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); //Same than above for t texture 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //What to do when some pixels are occupied by the same pixel. Mipmaps
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //What to do when some texels are on the same pixel.


//Pop-up menu initializing.
	

	draw_mode_menu = glutCreateMenu(DrawingModeInterface);
	glutAddMenuEntry("Points", POINTS);
	glutAddMenuEntry("Lines", LINES);
	glutAddMenuEntry("Solid", SOLID);
	glutAddMenuEntry("Enable or disable lighting", LIGHTS);
	glutAddMenuEntry("Enable or disable textures", TEXTURES);

	main_menu = glutCreateMenu(MenuInterface);
	glutAddSubMenu("Drawing mode", draw_mode_menu);
	glutAddMenuEntry("Start or stop animation", MOV);
	glutAddMenuEntry("Quit program", QUIT);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}


//***************************************************************************
// Main program.
//
// Initializes windows, assigns events and start main loop.
//***************************************************************************



int main(int argc, char **argv)
{
    

	//Calls glut initialization
	glutInit(&argc, argv);

    
    	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); //Sets RGB memory, double buffer memory, and z-buffer

    	//Left bottom corner of the window
    	glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    	//Window size
    	glutInitWindowSize(UI_window_width,UI_window_height);

    	//Create window
    	glutCreateWindow("Solar System");

    	//Drawing event function assignment.
    	glutDisplayFunc(draw_scene);
    
	//Resize window event function assignment.
    	glutReshapeFunc(change_window_size);
    
	//Normal key event function assignment.
    	glutKeyboardFunc(normal_keys);

    	//Special key event function assignment.
    	glutSpecialFunc(special_keys);

	//Set funtion to animate automatically.
	//glutIdleFunc(Animate);

	

    	//Initialization function.
    	initialize();

	

    	//Start glut event loop.
    	glutMainLoop();

    	return 0;

}
