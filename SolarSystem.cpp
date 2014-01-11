#include "SolarSystem.h"

SolarSystem::SolarSystem(){
	ObjetoRevolucionText sphere((char*) "Ply/esfera.ply", 30); //Reads the sphere ply file.

	sun = sphere;
	earth = sphere;
	moon = sphere;
	
	background = sphere;

	background.InvertirNormales(); //Its a concave object so it needs to flip its normals.


	erot_ang = 0.0;
	etra_ang = 0.0;
	mtra_ang = 0.0;
}

void SolarSystem::Draw(GLuint * textures){ 
	
		float sun_material[4] = {1.0, 1.0, 1.0, 1.0};
		float material[4] = {0.8,0.8,0.8,1.0};
		float zero[4] = {0.0,0.0,0.0,1.0};


	glPushMatrix();
		glBindTexture( GL_TEXTURE_2D, textures[0]);

		glColor3f(1.0, 0.4, 0.0); //Sun colour is orange if doesn't use any texture.
		
		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_material);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, zero);
		glMaterialfv(GL_FRONT, GL_SPECULAR, zero);
		sun.DrawObject();
	glPopMatrix();

	glPushMatrix();

		glColor3f(0.2, 0.6, 1.0); //Earth colour is blue if doesn't use any texture.
	
		glRotatef(etra_ang, 0, 1, 0); //Earth translation around sun.
		
		glTranslatef(3.0, 0.0, 0.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, zero); //Earth material parameters.
		glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
		glMaterialfv(GL_FRONT, GL_SPECULAR, zero);
		glPushMatrix();
			
			glRotatef(erot_ang, 0, 1, 0); //Earth rotation movement
			glScalef(0.5,0.5,0.5);
			glBindTexture( GL_TEXTURE_2D, textures[1]);
			earth.DrawObject();
		glPopMatrix();
		glColor3f(0.6, 0.6, 0.6); //Moon colour is grey if doesn't use any texture.
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, zero); //Moon material parameters.
		glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
		glMaterialfv(GL_FRONT, GL_SPECULAR, zero);
			glRotatef(mtra_ang, 0, 1, 0); //Moon translation movement (Around earth)
			glTranslatef(1.0, 0.0, 0.0);
			glScalef(0.25,0.25,0.25);
			glBindTexture( GL_TEXTURE_2D, textures[2]);
			moon.DrawObject();
		glPopMatrix();

	glPopMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, material); //Background material parameters.
		glMaterialfv(GL_FRONT, GL_DIFFUSE, zero);
		glMaterialfv(GL_FRONT, GL_SPECULAR, zero);
		glColor3f(0.0, 0.0, 0.0); //Background colour is black.

		glScalef(50,50,50);		
		glBindTexture( GL_TEXTURE_2D, textures[3]);
		background.DrawObject();
		
	glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, 0);
}

void SolarSystem::IncreaseAngles(){
	erot_ang -= 5.0;
	etra_ang += 1.0;
	mtra_ang += 12.0;
}

SolarSystem::~SolarSystem(){}
