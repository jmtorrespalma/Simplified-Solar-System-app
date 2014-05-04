
Simplified Solar System simulation app.
Version 1.5, 2013-2014

Last edit 04/May/2014

by Juan Manuel Torres Palma

GPLv3 license
A copy of the license is in the same directory than this file.
 
-------------------------------------------------------------------

INTRODUCTION

This is a simple OpenGL 2.0 program, very useful to learn and understand 
the basics of this API. OpenGL 2.0 is deprecated (currently on 4.0 version),
but lately has been recycled due to it's use in Android devices, 
which as far as i know, all of them include it.

This program was made with learning purposes (for me), and to practice my
OpenGL skills. I want to share it will everybody out there, because at any time,
a correct example on how something should be done, is very welcomed.

It's main features are: 
	-Drawing simple objects with simple data structures
	-Generation of revolution objects from a defined plane (cylinder 
	from a rectangle, sphere from a semicircle...).
	-Usage of simple objects to create a more complex(hierarchical)
	 one with transformations (e.g. Solar system object has 4 simple 
	objects like sun, moon...).
	-Objects animation with idle events (Earth translates around Sun).
	-Usage of multiple textures on simple objects.
	-Scene lighting to add sense of realism.
	-Ply and jpeg file formats management and usage for modelling 
	geometric objects and applying textures to them.
	-Event oriented programming with glut (OpenGL Utility Toolkit)
	adding pop-up menus, key events, intialization, etc. 
	

-------------------------------------------------------------------

FILES

All files here are properly documented with comments and examples. For more
info, check include and src directories.

	-ObjetoGrafico class provides an abstraction layer to simplify 
	the usage of 3D objects.
	-ObjetoRevolucionText class provides an easy way to generate 
	revolution objects from a plane polygon, and make it rotate around
	one of its edges. ./Ply directory includes some files already prepared
	to generate this kind of objects.
	-SolarSystem class is generator class of the scene it's drawn on my 
	main program.
	-File_ply_stl namespace is an implementation to read ply files of 
	triangles easily and create structures quickly and simple.
	-Vertex.h is an abstraction layer to simplify the usage and 
	understanding of vertexes. My program only uses float vertexes.
	-Main.cpp is the main program (obvious right?). It's totally documented 
	in there.
	-Makefile contains compiling directives. A deeper explanation can
	be found below.
	
	Folders

	-Ply contains some files in ply format to draw objects quickly. 
	Are divided in 2 groups:
		· Revolution planes (used by ObjetoRevolucionText): cilindrored
		esfera, cilindroconvexo, cubo, linea.
		· Simple objects (could be used by ObjetoGrafico): beethoven,
		big_dodge, ant.

	-Src contains several files needed to succesfully decode and read
	jpeg files (jpg_memsrc.cpp and jpg_readwrite.cpp), needed for textures. 
	I haven't written this code, only jpg_imagen, as an abstraction layer 
	to make my code easier to read.
	The rest of the code was written by Independent JPEG Group.

	-Textures has jpeg files needed to apply textures to objects like sun,
	moon, etc. 	  
	
	
--------------------------------------------------------------------

COMPILING

This program uses jpeg library, stl, OpenGL, glut, glu. All of them are linked
in Makefile, so in case it throws a compilation error, it could be probably 
cause you haven't installed any package.

I used Fedora 19 and Ubuntu 12.04, and works properly in both.

Needed packages on Fedora
libjpeg-turbo, libjpeg-turbo-devel, freeglut, freeglut-devel, mesa-libGL, 
mesa-libGLU, mesa-libGL-devel, mesa-libGLU-devel, mesa-dri-drivers, 
mesa-filesystem, mesa-libEGL, mesa-libglapi

-------------------------------------------------------------------

USE

At this point you must have compiled it. If you execute it you might see only 
a white background and 3 axis each one in a different colour. You can 
interactuate with the program in two different ways. 

	-Mouse. If you right click on the scene, a pop-up menu with 
	several options appears. It's pretty simple but that's one of the most
	complex things you can do with glut (deprecated too, I suggest to use
	qt or gtk+ instead of glut). Just have to click on any of them to 
	change our scene.


	-Keyboard. I added more functions to this than to mouse events.
	My program doesn distinguish between upercase and lowercase. 
	Here is a summary of all keys:
		· Arrow keys. Used to move in polar coordinates around axis
		origin.
		· PageUp and PageDown. Allows to increase or decrease distance
		to axis origin.
		· Q key. Quits the program.
		· S key. Draws the Solar System object in solid mode.
		· V key. Draws the Solar System object in points mode.
		· L key. Draws the Solar System object in lines mode.
		· 4 key. Enables lighting in scene.
		· 5 key. Enables textures in scene.
		· O key. Manually animates the scene.
		· B key. Moves light0 clockwise.
		· N key. Moves light0 counter clockwise.
		· T key. Automatically animates the scene. This option is
		disabled because increases CPU usage to 100%. To enable it
		should delete comment in glutIdleFunction.
			

-------------------------------------------------------------------

NOTES

1st.- My program and all of it's classes ONLY read and draw TRIANGLES! I did 
it that way to simplify, but you can easily add some functionality to 
ObjetoGrafico class to let it draw some other polygons. Believe me, it's 
pretty easy and will help you understand how that class works :).

2nd.- Some of my code, documentation, classes, etc, are in spanish cause 
i'm from Spain and it was originally written in my native language. I'm sorry
about that, i have tried to translate every sentence i have seen, but maybe
i have missed some.

3rd.- If you remove any file, or move it to other folder, I CAN'T guarantee
the program will WORK properly. This warning goes especially for textures. 
DON'T MOVE textures or program won't be able to find them. If you still 
want to, you should edit main program, in initialization function.

4th.- To have the program running properly, you should execute it from project main directory, for example, ./bin/Main (CORRECT). Its because to find Ply directory, uses current directory (searches for ./Ply). In case you want to run it, put the correct path in the source code, using full path to run it from any directory you want.

---------------------------------------------------------------------

