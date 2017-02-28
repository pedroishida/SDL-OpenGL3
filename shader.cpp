#include "shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
}

bool Shader::Init(const char *vertexFilename, const char *fragmentFilename)
{
    int size = 0;
    int status = 0;
    char *log = NULL;

    program = glCreateProgram();

    glBindAttribLocation(program, 0, "in_position");
    glBindAttribLocation(program, 1, "in_color");

    if (!LoadShader(&vertexShader, vertexFilename, GL_VERTEX_SHADER)) {
        return false;
    }
    if (!LoadShader(&fragmentShader, fragmentFilename, GL_FRAGMENT_SHADER)) {
        return false;
    }

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status) {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);
        log = new char[size];
        glGetProgramInfoLog(program, size, &size, log);
        std::fprintf(stderr, "Failed to link shader:\n%s\n", log);
        delete [] log;
        return false;
    }

    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
    if (!status) {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);
        log = new char[size];
        glGetProgramInfoLog(program, size, &size, log);
        fprintf(stderr, "Invalid shader program:\n%s\n", log);
        delete [] log;
        return false;
    }

    worldLocation = glGetUniformLocation(program, "world");

    return true;
}

bool Shader::LoadShader(GLuint *shader, const char *filename, GLenum shaderType)
{
    int size = 0;
    int compiled = 0;
    char *src = NULL;
    char *log = NULL;
    std::FILE *inputfile = NULL;

    inputfile = std::fopen(filename, "r");
    if (NULL == inputfile) {
        std::fprintf(stderr, "Failed to open file: %s.\n", filename);
        return false;
    }

    std::fseek(inputfile, 0, SEEK_END);
    size = std::ftell(inputfile);
    std::rewind(inputfile);
    src = new char[size];

    if (size != (int) std::fread(src, sizeof(char), size, inputfile)) {
        std::fprintf(stderr, "Failed to read file: %s.\n", src);
        return false;
    }

    std::fclose(inputfile);

    *shader = glCreateShader(shaderType);
    glShaderSource(*shader, 1, &src, &size);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &compiled);
    if (0 == compiled) {
        glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &size);
        log = new char[size];
        glGetShaderInfoLog(*shader, size, &size, log );
        std::fprintf(stderr, "Failed to compile shader:\n%s\n", log);
        delete [] log;
        return false;
    }

    glAttachShader(program, *shader);

    delete [] src;

    return true;
}

void Shader::UseProgram()
{
    glUseProgram(program);
}

void Shader::Clean()
{
    glUseProgram(0);

    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    glDeleteProgram(program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Transform(float matrix[4][4])
{
    if (0xFFFFFFFF != worldLocation) {
        glUniformMatrix4fv(worldLocation, 1, GL_TRUE, &matrix[0][0]);
    }
}
