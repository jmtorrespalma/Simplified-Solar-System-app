//******************************************************************************
// class to read ply files of triangles
//
// Domingo Martín and Juan Manuel Torres Palma
// GPLv3
//******************************************************************************

#ifndef _READ_PLY
#define _READ_PLY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <assert.h>

using namespace std;

namespace _file_ply
{


//**********************************************************************
//
// read: reads a ply file and stores it in vertices and faces vectors
//
// * 'nombreArchivo' should include .ply extension
// * if there is any error, aborts and returns -1
// * clears 'vertices' and 'faces'
// * reads a .ply file and loads it in vectors
// * only reads triangles plys 
// * doesn't read normals, colours or texture coordinates

void read( const char * nombreArchivo, vector<float> &Vertices,vector<int> &Faces );
   
} ;

#endif // _READ_PLY
