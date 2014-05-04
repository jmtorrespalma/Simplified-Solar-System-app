# Makefile
#
# Juan Manuel Torres Palma
#
# project directories
#

SRC = ./src
INC = ./include
BIN = ./bin
OBJ = ./obj
LIB = ./lib

# project files
#

SRC_FILES = $(wildcard $(SRC)/*.cpp)
OBJ_FILES = $(addprefix $(OBJ)/, $(notdir $(SRC_FILES:.cpp=.o)))


# binary file name
#

TARGETS= $(BIN)/Main



# compiler flags(C and C++). -I is used to point to which directories could
# allocate a header file.
# -g option is used for debugging with gdb.
#
CFLAGS=    -g -Wall -DXWINDOWS -DSHM -I/usr/include -I$(INC)
CXXFLAGS=  $(CFLAGS)


# Linker flags.
# 
#

LDFLAGS=  -lGLU -lGL -lglut -ljpeg

# Compiler definition.
#

CXX = g++

# Default rule
#

default : $(TARGETS)

# Execution rule
#

$(TARGETS) : $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

$(OBJ)/%.o : $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

#$(TARGETS) : ObjetoGrafico.o ObjetoRevolucionText.o SolarSystem.o Main.o file_ply_stl.o Sources/jpg_imagen.o Sources/jpg_memsrc.o Sources/jpg_readwrite.o

#	$(CC) -o $@ $(CXXFLAGS) ObjetoGrafico.o ObjetoRevolucionText.o SolarSystem.o Sources/jpg_imagen.o Sources/jpg_memsrc.o Sources/jpg_readwrite.o file_ply_stl.o Main.o  $(LDFLAGS)


#
#
clean:
	rm -f $(OBJ)/*.o
	rm -f $(TARGETS)

#
#
redo:

#

#
#
superclean:
	rm -f $(OBJ)/*.o
	rm -f $(SRC)/*~
	rm -f $(TARGETS)

#
#
tgz: superclean
	tar -czvf $(TARGETS).tgz *

