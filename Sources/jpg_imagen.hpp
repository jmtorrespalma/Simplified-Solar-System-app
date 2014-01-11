#ifndef JPG_IMAGEN_HPP
#define JPG_IMAGEN_HPP

#include <string>

// class 'Imagen'
//
// abstraction layer over class jpg::JpegFile
// stores jpeg image pixels in memory
// 

namespace jpg {

class Imagen {
	public:

	// Initializes an instance and tries to load JPEG 
 	// file in nombreArchivo
	Imagen( const std::string & nombreArchivo ) ;

	// Initializes an instance and tries to load JPEG 
 	// file in wstr
	Imagen( const std::wstring & wstr ) ;

	// Returns a pointer to pixels stored by rows, three
	// bytes per pixel, in RGB order. 	
	unsigned char * leerPixels()  ;

	// Returns a pointer to a pixel.
	unsigned char * leerPixel( unsigned ix, unsigned iy ) ;

	// Returns columns number of image
	unsigned long tamX() const ;

	// Returns rows number of image
	unsigned long tamY() const ;

	// Tries to write the image in a jpeg file
	void escribirEn( const std::string & nombreArchivo );
	
	// Deletes the buffer
	~Imagen () ;

	private:
    
   	unsigned char * buf  ;  // pixels buffer
	unsigned int    w, h ;  // width and height

};

}

#endif
