#Makefile for the oglTry application

CXX = g++
APP = oglTry
SRCS = oglTry.cpp ShaderSourceFile.cpp
OBJS = $(SRCS:.cpp=.o)
LDOPTIONS = -lglut -lGLEW

all : $(APP)

$(APP) : $(OBJS)
	$(CXX) -o $@ $^ $(LDOPTIONS)

oglTry.o : ShaderSourceFile.h oglTry.cpp
	$(CXX) -g -c -o $@ oglTry.cpp

ShaderSourceFile.o : ShaderSourceFile.h ShaderSourceFile.cpp
	$(CXX) -g -c -o $@ ShaderSourceFile.cpp	

clean :
	rm -f $(APP) $(OBJS)