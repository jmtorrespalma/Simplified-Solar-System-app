#include "ObjetoGrafico.h"
#include "file_ply_stl.h"
#include <GL/gl.h>

ObjetoGrafico::ObjetoGrafico(){};

ObjetoGrafico::ObjetoGrafico(vector < _vertex3f > &unos_vertices, vector<int> &unas_caras ){

	this -> vertices = unos_vertices;
	this -> caras = unas_caras;
}

ObjetoGrafico::ObjetoGrafico(char* file){

	vector<float> vector_vertices;

	_file_ply::read(file, vector_vertices, this->caras);
	this->vertices = PasarFloatAVertex(vector_vertices);


	CalcularNormalesCara();
	CalcularNormalesVertices();

}

vector < _vertex3f > ObjetoGrafico::VerticesDeCara(int cara){
	vector< _vertex3f > solucion;
	_vertex3f vertice;

	solucion.push_back(this -> vertices.at(this -> caras.at(cara*3)));
	solucion.push_back(this -> vertices.at(this -> caras.at(cara*3+1)));
	solucion.push_back(this -> vertices.at(this -> caras.at(cara*3+2)));

	return solucion;
}

_vertex3f ObjetoGrafico::Vertice(int indice){
	return (this -> vertices.at(indice));
}


ObjetoGrafico & ObjetoGrafico::operator= (const ObjetoGrafico & objeto){
	this -> vertices = objeto.vertices;
	this -> caras = objeto.caras;
	this ->	normal_cara = objeto.normal_cara;
	this -> normal_vertice = objeto.normal_vertice;
	this -> texel_vertex = objeto.texel_vertex;
	
	return *this;
}

ObjetoGrafico::~ObjetoGrafico(){}


void ObjetoGrafico::CalcularNormalesCara(){
	
	_vertex3f resultado, vector1, vector2;

	normal_cara.clear();

	for(int i = 0; i < caras.size(); i = i + 3){  //Obtains faces normal with cross product.
		vector1 = vertices.at(caras.at(i+2)) - vertices.at(caras.at(i));
		vector2 = vertices.at(caras.at(i+1)) - vertices.at(caras.at(i));
		resultado = vector2.cross_product(vector1);		

		resultado.normalize();
		normal_cara.push_back(resultado); 
	}

}

void ObjetoGrafico::CalcularNormalesVertices(){ //Gets vertices normal.
	vector< _vertex3f > sumas; //Keeps adding faces normals.
	vector<int> n_caras; //Number of faces that use a single vertex.
	_vertex3f cero(0.0,0.0,0.0);

	normal_vertice.clear();

	for (int i = 0; i < NumVertices(); ++i){ //Saves zeroes to keep adding faces normal values in next loop.
		sumas.push_back(cero);
		n_caras.push_back(0);
	}

	for (int i = 0; i < caras.size(); ++i){
		sumas.at(caras.at(i)) += normal_cara.at(i / 3);
		++(n_caras.at(caras.at(i)));
	}
	
	for (int i = 0; i < NumVertices(); ++i){ //Divides by number of faces where that vertex is used and normalizes. 
		normal_vertice.push_back(sumas.at(i) / n_caras.at(i));
		normal_vertice.at(i).normalize();
	} 

}



vector< _vertex3f > ObjetoGrafico::PasarFloatAVertex(vector<float> &Vertices){

	vector< _vertex3 <float> > resultado;
	_vertex3<float> vertice;

	for (int i = 0; i < Vertices.size(); i = i+3){
		vertice.x = Vertices.at(i);
		vertice.y = Vertices.at(i+1);
		vertice.z = Vertices.at(i+2);
		resultado.push_back(vertice);
	}

	return resultado;
}

void ObjetoGrafico::DrawCaraTriangular(vector < _vertex3f > &cara){

	glBegin(GL_TRIANGLES);
		glVertex3f(cara.at(0).x, cara.at(0).y, cara.at(0).z);
		glVertex3f(cara.at(1).x, cara.at(1).y, cara.at(1).z);
		glVertex3f(cara.at(2).x, cara.at(2).y, cara.at(2).z);
		glEnd();

}

void ObjetoGrafico::InvertirNormales(){
	
	for (int i = 0; i < normal_cara.size(); ++i){
		normal_cara.at(i).x *= -1;
		normal_cara.at(i).y *= -1;
		normal_cara.at(i).z *= -1;
	}

	for (int i = 0; i < normal_vertice.size(); ++i){
		normal_vertice.at(i).x *= -1;
		normal_vertice.at(i).y *= -1;
		normal_vertice.at(i).z *= -1;
	}

}

void ObjetoGrafico::PrintNormals(){ //Used in debugging.
	for (int i = 0; i < normal_cara.size(); ++i)
		cout << normal_cara.at(i).x << " " << normal_cara.at(i).y << " " << normal_cara.at(i).z << endl;
}

void ObjetoGrafico::DrawCaraTriangularIluminada(int indice){ 	//Can only be used if a texel assignment method is defined previously, if its not
								//will throw a segmentation fault due to accessing texel_vertex not initialized.
								//That function is defined in ObjetoRevolucionText

		int vertice1 = caras.at(3*indice);
		int vertice2 = caras.at(3*indice+1);
		int vertice3 = caras.at(3*indice+2);

	glBegin(GL_TRIANGLES);
		
		glTexCoord2f(texel_vertex.at(vertice1).x, texel_vertex.at(vertice1).y);
		glNormal3f(normal_vertice.at(vertice1).x, normal_vertice.at(vertice1).y, normal_vertice.at(vertice1).z);
		glVertex3f(vertices.at(vertice1).x, vertices.at(vertice1).y, vertices.at(vertice1).z);

		glTexCoord2f(texel_vertex.at(vertice2).x, texel_vertex.at(vertice2).y);
		glNormal3f(normal_vertice.at(vertice2).x, normal_vertice.at(vertice2).y, normal_vertice.at(vertice2).z);
		glVertex3f(vertices.at(vertice2).x, vertices.at(vertice2).y, vertices.at(vertice2).z);

		glTexCoord2f(texel_vertex.at(vertice3).x, texel_vertex.at(vertice3).y);
		glNormal3f(normal_vertice.at(vertice3).x, normal_vertice.at(vertice3).y, normal_vertice.at(vertice3).z);
		glVertex3f(vertices.at(vertice3).x, vertices.at(vertice3).y, vertices.at(vertice3).z);
	glEnd();

}

void ObjetoGrafico::DrawVertices()
{
	glColor3f(1,0,0);
	glPointSize(5);

	glBegin(GL_POINTS);
	for (int i = 0; i < (*this).NumVertices(); ++i){
		glVertex3f((*this).Vertice(i).x, (*this).Vertice(i).y, (*this).Vertice(i).z);
	}
	glEnd();
}

void ObjetoGrafico::DrawObject(){
	for (int i = 0; i < (*this).NumCaras(); ++i){
		DrawCaraTriangularIluminada(i);
	}
}

void ObjetoGrafico::DrawAlambre(){

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	DrawObject();	

}

	
void ObjetoGrafico::DrawAjedrez(){

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (int i = 0; i < (*this).NumCaras(); ++i){

		if (i % 2 == 0)
			glColor3f(0.5,0,1);
		else
			glColor3f(1,0,0.3); 

		DrawCaraTriangularIluminada(i);

	}

}

void ObjetoGrafico::DrawSolido(){


	glPolygonMode(GL_FRONT, GL_FILL);

	DrawObject();
}
