#ifndef SPACE_H
#define SPACE_H

#include <cstdio>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "shader.h"

class Space
{
    unsigned int i, j;
    unsigned int width;
    unsigned int height;
    int error_code;
    float aspectRatio;
    float fieldOfView;
    float zNear, zFar;
    float xRot;
    float yRot;
    float zRot;
    float xTrans;
    float yTrans;
    float zTrans;
    SDL_Window* display;
    SDL_Event event;
    SDL_GLContext context;
    GLuint vertexBuffers[1];
    GLuint vertexArrays[1];
    GLuint indexBuffers[1];
    Shader shader;
    protected:
        int Init();
        void Quit();
        void CalculateWorldMatrix();
    public:
        Space();
        Space(unsigned int, unsigned int);
        ~Space();
        unsigned short int HandleEvents();
        void LoadBuffer();
        void Render();
        int GetError();
};
#endif
