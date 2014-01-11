//**************************************************/
//
//Juan Manuel Torres Palma
//
//Class used to encapsulate 3D graphic objects created with triangles.
//
//Contains vertex, faces, texels assigned to each vertex,
//vertex normal, face normal, and all related methods.
//
//**************************************************/

#ifndef _OBJ_GRAF_
#define _OBJ_GRAF_

#include <vector>
#include "vertex.h"

using namespace std;

class ObjetoGrafico{

protected:
	vector< _vertex3f > vertices;
	vector<int> caras; //Represent indexeses of vertexes // caras.at(0...2) describe vertexes of face 0, and so on. 

	vector< _vertex2f > texel_vertex; //Texel assigned to each vertex.

	vector< _vertex3f > normal_cara; //Faces normals.
	vector< _vertex3f > normal_vertice; //Vertexes normals.

	vector< _vertex3f > PasarFloatAVertex(vector<float> &vector_floats); //Formats a float vector into a vertex3f one.
	void DrawCaraTriangular(vector < _vertex3f > &cara); //Draws a face
	
	void DrawCaraTriangularIluminada(int indice); //Draws an iluminated and textured faced.

	void CalcularNormalesCara(); //Calculates each face normal.
	void CalcularNormalesVertices(); //Calculates each vertex normal.


	

public:
	ObjetoGrafico();

	void PrintNormals();

	//***Flips object normals (Needed in case of objects seen from the inside).
	void InvertirNormales();

	//***Creates a new object with a vertexes and faces vectors.
	ObjetoGrafico(vector< _vertex3f > &unos_vertices, vector <int> &unas_caras);

	//***Reads a ply file and creates a new object.	
	ObjetoGrafico(char* ply_file);

	//***Returns 3 vertexes that form a face specified by cara argument.
	vector< _vertex3f > VerticesDeCara(int cara);

 	//***Returns vertex related to indice index.
	_vertex3f Vertice(int indice);


	inline int NumVertices() const {return (this -> vertices).size();}

	inline int NumCaras() const {return ((this -> caras).size()/3);}

	ObjetoGrafico & operator= (const ObjetoGrafico & objeto);

	~ObjetoGrafico();
	
	void DrawObject();

	void DrawVertices();
	
	void DrawAlambre();

	void DrawSolido();

	void DrawAjedrez();
};

#endif
