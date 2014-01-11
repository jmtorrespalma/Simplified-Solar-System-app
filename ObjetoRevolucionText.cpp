#include "ObjetoRevolucionText.h"
#include <cmath>
#include <iostream>

#define PI 3.141592

ObjetoRevolucionText::ObjetoRevolucionText(){}

ObjetoRevolucionText::ObjetoRevolucionText(char* file, int n_particiones){ //Only works with 2D polygons, placed on positive xy axis.

	vector< float > vector_vertices;
	vector <int> desechado;

	_file_ply::read(file, vector_vertices, desechado);
	this -> vertices_generadores = PasarFloatAVertex(vector_vertices);


	tapa_sup = (vertices_generadores.at(0).x == 0); //Calculates if there is a top cover.
	tapa_inf = (vertices_generadores.at(vertices_generadores.size()-1).x == 0); //Calculates if there is a bottom cover.

	CalcularVertexandTexel(n_particiones);


}


void ObjetoRevolucionText::CalcularVertexandTexel(int n_cortes){

	
	_vertex3f aux;

	_vertex2f texel;

	float texel_x = 1.0 / n_cortes, texel_y = 1.0 / NumVerticesGen();

	float angulo = 360.0 / n_cortes;
	
	vertices.clear();
		
		
	for (int j = 0; j <= n_cortes; ++j){

		for (int i = 0; i < NumVerticesGen(); ++i){//This loop creates repeated vertex (top and bottom) to use textures.

			aux.x = vertices_generadores.at(i).x * cos((angulo * j) * (PI/180));
			aux.z = vertices_generadores.at(i).x * sin((angulo * j) * (PI/180));
			aux.y = vertices_generadores.at(i).y;
			vertices.push_back(aux);

			texel.x = 1.0 - (texel_x * j); //To avoid reversed textures.
			texel.y = texel_y * i;
			texel_vertex.push_back(texel);

		}
	}

		
		
	this -> particiones = n_cortes;

	CalcularCaras();
	CalcularNormalesCara();		
	CalcularNormalesVertices();
	
}

void ObjetoRevolucionText::CalcularCaras(){

	int pos_sup, pos_inf;
	int n_sin_tapas = NumVertices() - tapa_sup - tapa_inf; //Number of vertexes without counting top and bottom.
	int n_gen_sin_tapas = NumVerticesGen() - tapa_inf - tapa_sup; // Number of generator vertexes without counting top and bottom.

	caras.clear();
	normal_cara.clear();
	normal_vertice.clear();

	for (int i = 0; i < particiones; ++i){ // Draws all triangles net
		for (int j = 0; j < (NumVerticesGen() - 1); ++j){

			int posicion_actual = (i * NumVerticesGen()) + j;
			bool aux = (tapa_inf && j == NumVerticesGen() - 2); //Used to not duplicate faces in top
			bool aux2 = (tapa_sup && j == 0 );

			if (!aux){
				caras.push_back(posicion_actual);
				caras.push_back(posicion_actual + NumVerticesGen() + 1);
				caras.push_back(posicion_actual + 1);
			}
			
			if (!aux2){
				caras.push_back(posicion_actual);
				caras.push_back(posicion_actual + NumVerticesGen());
				caras.push_back(posicion_actual + 1 + NumVerticesGen());
			}

		}

	}

}



void ObjetoRevolucionText::DrawPuntos(){
	DrawVertices();
}

int ObjetoRevolucionText::NumVerticesGen(){
	return vertices_generadores.size();

}

void ObjetoRevolucionText::DrawPolilinea(){ 

	float x,y,z;
	int n_gen_sin_tapa = NumVerticesGen() - tapa_sup - tapa_inf;
	int pos_sup, pos_inf;

	if(tapa_inf){ // Try to find the top or bottom vertex in case it exists.
		pos_inf = NumVertices() - 1;
		if (tapa_sup)
			pos_sup = NumVertices() - 2;
	}
	else if(tapa_sup)
		pos_sup = NumVertices() - 1;



	for (int j = 0; j < particiones; ++j){

		glBegin(GL_LINE_STRIP);
		
		if(tapa_sup)
			glVertex3f(vertices.at(pos_sup).x, vertices.at(pos_sup).y, vertices.at(pos_sup).z);	
	
		for (int i = 0; i < n_gen_sin_tapa; ++i){

			x = vertices.at(i + (j * n_gen_sin_tapa)).x;
			z = vertices.at(i + (j * n_gen_sin_tapa)).z;
			y = vertices.at(i + (j * n_gen_sin_tapa)).y;

			glVertex3f(x, y, z);

		}

		if(tapa_inf)
			glVertex3f(vertices.at(pos_inf).x, vertices.at(pos_inf).y, vertices.at(pos_inf).z);	

		glEnd();

	}
}



