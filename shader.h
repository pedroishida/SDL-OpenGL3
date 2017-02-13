#include <cmath>
#include <cstdio>

#include <GL/glew.h>

class Shader
{
    GLuint program;
    GLuint vertexShader, fragmentShader;
    GLuint worldLocation;
    public:
        Shader();
        ~Shader();
        bool Init(const char*, const char*);
        void Clean();
        bool LoadShader(GLuint*, const char*, GLenum);
        void UseProgram();
        void Transform(float [4][4]);
};
