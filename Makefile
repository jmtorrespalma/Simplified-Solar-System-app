# Makefile
#
# binary file name
#
TARGETS= Main

# compiler flags(C and C++). -I is used to point to which directories could
# allocate a header file.
# -g option is used for debugging with gdb.
#
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I.
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I. -I./Sources

# Linker flags.
# 
#
LDFLAGS=  -lGLU -lGL -lglut -ljpeg

# Compiler definition.
#
CC = g++

# Default rule
#
default : $(TARGETS)

# Execution rule
#
$(TARGETS) : ObjetoGrafico.o ObjetoRevolucionText.o SolarSystem.o Main.o file_ply_stl.o Sources/jpg_imagen.o Sources/jpg_memsrc.o Sources/jpg_readwrite.o
	$(CC) -o $@ $(CXXFLAGS) ObjetoGrafico.o ObjetoRevolucionText.o SolarSystem.o Sources/jpg_imagen.o Sources/jpg_memsrc.o Sources/jpg_readwrite.o file_ply_stl.o Main.o  $(LDFLAGS)


#
#
clean:
	rm -f *.o
	rm -f $(TARGETS)

#
#
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *

