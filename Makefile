CPPFLAGS=-Wall -O3

build: openGL

openGL: openGL.cpp space.cpp space.h shader.cpp shader.h -lGL -lGLU -lGLEW -lSDL2

.PHONY: clean
clean:
	-rm -f openGL
