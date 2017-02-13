#include <cstdio>

#include <GL/glew.h>

class Shader
{
    GLuint program;
    GLuint vertexShader, fragmentShader;
    public:
        Shader();
        ~Shader();
        bool Init(const char*, const char*);
        void Clean();
        bool LoadShader(GLuint*, const char*, GLenum);
        void UseProgram();
};
