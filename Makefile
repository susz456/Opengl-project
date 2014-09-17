CC=g++
OBJS=*.cpp ./core/*.cpp
LIBS=-lGL -lglut -lGLEW -g
program: $(OBJS)
	$(CC) $(OBJS) -o program $(LIBS)
