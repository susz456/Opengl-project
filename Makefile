CC=g++
OBJS=*.cpp
LIBS=-lGL -lglut -lGLEW -g
program: $(OBJS)
	$(CC) $(OBJS) -o program $(LIBS)
