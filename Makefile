#Makefile for the oglTry application

CXX = g++
APP = oglTry
SRCS = oglTry.cpp ShaderSourceFile.cpp math_3d.cpp
OBJS = $(SRCS:.cpp=.o)
LDOPTIONS = -lglut -lGLEW

all : $(APP)

$(APP) : $(OBJS)
	$(CXX) -o $@ $^ $(LDOPTIONS)

oglTry.o : math_3d.h ShaderSourceFile.h oglTry.cpp
	$(CXX) -g -c -o $@ oglTry.cpp

ShaderSourceFile.o : ShaderSourceFile.h ShaderSourceFile.cpp
	$(CXX) -g -c -o $@ ShaderSourceFile.cpp	

math_3d.o : math_3d.h math_3d.cpp
	$(CXX) -g -c -o $@ math_3d.cpp	

clean :
	rm -f $(APP) $(OBJS)