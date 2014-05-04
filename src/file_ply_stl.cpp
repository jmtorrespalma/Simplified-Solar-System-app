//**********************************************************************
// class to read ply files of triangles
//
// Domingo Martín, Carlos Ureña and Juan Manuel Torres Palma
// GPLv3
//**********************************************************************



#include "file_ply_stl.h"


namespace _file_ply {

//**********************************************************************

void error( const char *msgError ){
   	using namespace std ;
   	cout  << endl
         << "Error: " << msgError << endl 
         << "program aborted." << endl
         << flush ; 
        
   exit(-1);
}

// read buffer, to store lines from ply file.

const streamsize bufferCapacity = streamsize(10)*streamsize(1024) ;
char buffer[(unsigned long)(bufferCapacity)];



void read( const char * nombreArchivo, vector<float> &vertices, vector<int> &faces ){

   // ply models in:
   // http://graphics.im.ntu.edu.tw/~robin/courses/cg03/model/
   // http://people.sc.fsu.edu/~jburkardt/data/ply/ply.html
   
	using namespace std ;

   	const string sfn = string(nombreArchivo);
   
   	string token ;
   	unsigned long long int nVertexs = 0, nFaces = 0 ;
   	unsigned state = 0; // 0 before reading 'element vertex', 1 before reading 'element face', 2 after both
   	bool inHeader = true ;

   	ifstream src( sfn.c_str() ) ; // open the file
      
   	if (!src.is_open()) {
      	string msg = string("can't open file '") + sfn + "' for reading." ; 
      	error(msg.c_str());
   	}
    
   	src >> token ;

   	if (token != "ply")
      	error("the file doesn't start with'ply'.");

   	src.getline(buffer,bufferCapacity);

   	cout << "reading triangles net '" + sfn + "' " << flush ;

   	// read header:
   
   	while(inHeader){

      		if (src.eof()) 
         		error("EOF didn't expected in header");

     		src >> token ;

     		if (token == "end_header"){  
			if (state != 2)
           			error("can't find 'element vertex' nor 'element face' in header");

        		src.getline(buffer,bufferCapacity);
        		inHeader = false ;
     		}

     		else if ( token == "comment" ){  
			src.getline(buffer,bufferCapacity);
        		//cout << "  comment: " << buffer << endl ;
     		}

     		else if ( token == "format" ){  
			src >> token ;
        		if ( token != "ascii" ){
				string msg = string("can't read format different to 'ascii', found format is: '")+token+"'" ;
           			error(msg.c_str());
        		}
        
			src.getline(buffer,bufferCapacity);
 		}

     		else if ( token == "element" ){  
			src >> token ;
	        	if ( token == "vertex" ){  
				if ( state != 0 )
              				error("'element vertex' comes after 'element face'");
           			src >> nVertexs ;
           		//cout << "  number of vertexes == " << nVertexs << endl ;
           		state = 1;
        		}
        		else if ( token == "face" ){  
				if ( state != 1 )
              				error("warning: 'element vertex' comes after 'element face'");
           			src >> nFaces ;
           			//cout << "  number of faces == " << nFaces << endl ;
           			state = 2 ;
        		}

        		else{  
				cout << "  element '" + token + "' ignored." << endl ;
        		}
        		src.getline(buffer,bufferCapacity);
     		}

     		else if (token == "property"){  
		
		src.getline(buffer,bufferCapacity); // ignore properties, so far ...
     		}

   	} // end of while( inHeader )

   	if ( nVertexs == 0 || nFaces == 0 )
      		error("There are zero vertexes or faces in file");
      
   	cout << "  (" << nVertexs << " vértices, " << nFaces << " caras)" << endl << flush ;
   
      
   	// read vertexes:
      
   	vertices.resize( nVertexs*3 );

   	//cout << "  reading " << nVertexs << " vertexes ...." << endl << flush ;
     
   	for (unsigned long long iv = 0 ; iv < nVertexs ; ++iv){
      		if (src.eof()) 
         		error("Not expected EOF in vertexes list");

      		double x,y,z ;

      		src >> x >> y >> z ;
      		//cout << "vertex #" << iv << " readed: (" << x << "," << y << "," << z << ")" << endl ;
      
      		src.getline(buffer,bufferCapacity); // ignore more properties, so far ...
      
      		// add new vertex
      		unsigned long long base = iv*3 ;
      		vertices[base+0] = x ;
      		vertices[base+1] = y ;
      		vertices[base+2] = z ; 
   	}

   	//cout << "  end vertex list" << endl << flush ;
   	//cout << "  reading " << nFaces << " faces ...." << endl << flush ;
   
   	// read faces.
   
   	faces.resize( nFaces*3 );
   
   	for(unsigned long long ifa = 0 ; ifa < nFaces ; ++ifa){
      		if (src.eof()) 
         		error("Not expected EOF in faces list");

      		unsigned nv ;
      		src >> nv ;
      		//cout << "reading face #" << ifa << " with " << nv << " vertexes: " ;
      
      		if (nv != 3)
         		error("Face found with a number of vertexes different to 3");
         
      		unsigned long long iv0, iv1, iv2 ;

      		src >> iv0 >> iv1 >> iv2 ;
      		//cout << " " << iv0 << ", " << iv1 << ", " << iv2 << endl ;

      		src.getline(buffer,bufferCapacity); // ignore more properties, so far ...

      		unsigned long long base = ifa*3 ; 
      		faces[base+0] = iv0 ;
      		faces[base+1] = iv1 ;
      		faces[base+2] = iv2 ;
   	}

   	//cout << "  end face list." << endl ;
   	//cout << "ply file readed" << endl << flush ;
   
   	return ;
}


} // end namespace _file_ply
