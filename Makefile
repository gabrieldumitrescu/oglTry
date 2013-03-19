#Makefile for the oglTry application

CXX = g++
APP = oglTry
SRCS = oglTry.cpp
OBJS = $(SRCS:.cpp=.o)
LDOPTIONS = -lglut -lGLEW

all : $(APP)

$(APP) : $(OBJS)
	$(CXX) -o $@ $^ $(LDOPTIONS)

oglTry.o : oglTry.cpp
	$(CXX) -g -c -o $@ $^

clean :
	rm -f $(APP) $(OBJS)