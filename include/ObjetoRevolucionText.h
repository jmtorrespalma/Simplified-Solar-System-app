//**************************************************/
//
//Juan Manuel Torres Palma
//
//Class used to create revolution objects (generated from a rotating plane).
//
//Inherites from ObjetoGrafico so keeps all its functionality.
//
//**************************************************/

#ifndef _OBJ_REV_
#define _OBJ_REV_

#include "ObjetoGrafico.h"
#include "vertex.h"
#include <vector>
#include <GL/gl.h>
#include "file_ply_stl.h"

class ObjetoRevolucionText : public ObjetoGrafico{ 

private:

	vector < _vertex3f > vertices_generadores; //Generator plane vertexes.

	bool tapa_sup; //Bool variable. Will be equal to 1 if has top faces.

	bool tapa_inf; //Bool variable. Will be equal to 1 if has bottom faces.

	int particiones; //Number of partitions of the object.

	void CalcularCaras(); //Calculate faces once vertexes have been calculated.


public:
	ObjetoRevolucionText(char* file, int n_particiones); //File is a ply file with generator plane coordinates.

	ObjetoRevolucionText();

	int NumVerticesGen(); //Returns number of generator plane vertexes.

	void DrawPuntos(); //Draws object with points.

	void DrawPolilinea(); //Draws only rotated generated vertexes, joined with vertical lines. 

	void CalcularVertexandTexel(int n_cortes); //Assigns a texel to each vertex.

};

#endif
