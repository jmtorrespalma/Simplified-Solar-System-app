//**************************************************/
//
//Juan Manuel Torres Palma
//
//Class used to represent our simplified solar system.
//
//
//**************************************************/

#ifndef _SOLAR_SYSTEM_H_
#define _SOLAR_SYSTEM_H_

#include "ObjetoRevolucionText.h"

class SolarSystem : public ObjetoGrafico{
	private:
	
	ObjetoRevolucionText sun, earth, moon, background; //Represented stars.

	float erot_ang, etra_ang, mtra_ang; 	//Rotation and translation angles
						// erot_ang = Earth rotation angle
						// etra_ang = Earth translation angle
						// mtra_ang = Moon translation angle

	public:

	SolarSystem(); //Initializes all solar system stars.

	void Draw(GLuint * textures); //Needs textures as an argument, cause were initialized in main program.

	void IncreaseAngles(); //Animation function.

	~SolarSystem();
};

#endif
