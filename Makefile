#Makefile for the oglTry application

CXX = g++
APP = oglTry
SRCS = oglTry.cpp ShaderSourceFile.cpp math_3d.cpp pipeline.cpp
OBJS = $(SRCS:.cpp=.o)
LDOPTIONS = -lglut -lGLEW

all : $(APP)

$(APP) : $(OBJS)
	$(CXX) -o $@ $^ $(LDOPTIONS)

oglTry.o : math_3d.h ShaderSourceFile.h pipeline.h oglTry.cpp
	$(CXX) -g -c -o $@ oglTry.cpp

ShaderSourceFile.o : ShaderSourceFile.h ShaderSourceFile.cpp
	$(CXX) -g -c -o $@ ShaderSourceFile.cpp	

math_3d.o : math_3d.h math_3d.cpp
	$(CXX) -g -c -o $@ math_3d.cpp	

pipeline.o: pipeline.h pipeline.cpp
	$(CXX) -g -c -o $@ pipeline.cpp	

clean :
	rm -f $(APP) $(OBJS)