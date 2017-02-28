#include "space.h"

const GLfloat cube[24][10] = {
    //front face
    {-0.5,-0.5,-0.5, 0.0, 0.0,-1.0, 1.0, 1.0, 1.0, 1.0},//0: front bottom left
    { 0.5,-0.5,-0.5, 0.0, 0.0,-1.0, 1.0, 1.0, 1.0, 1.0},//1: front bottom right
    { 0.5, 0.5,-0.5, 0.0, 0.0,-1.0, 1.0, 1.0, 1.0, 1.0},//2: front top right
    {-0.5, 0.5,-0.5, 0.0, 0.0,-1.0, 1.0, 1.0, 1.0, 1.0},//3: front top left
    //left face
    {-0.5,-0.5, 0.5,-1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0},//4: back bottom left
    {-0.5,-0.5,-0.5,-1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0},//5: front bottom left
    {-0.5, 0.5,-0.5,-1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0},//6: front top left
    {-0.5, 0.5, 0.5,-1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0},//7: back top left
    //back face
    { 0.5,-0.5, 0.5, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0},//8: back bottom right
    {-0.5,-0.5, 0.5, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0},//9: back bottom left
    {-0.5, 0.5, 0.5, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0},//10: back top left
    { 0.5, 0.5, 0.5, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0},//11: back top right
    //right face
    { 0.5,-0.5,-0.5, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0},//12: front bottom right
    { 0.5,-0.5, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0},//13: back bottom right
    { 0.5, 0.5, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0},//14: back top right
    { 0.5, 0.5,-0.5, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0},//15: front top right
    //top face
    {-0.5, 0.5,-0.5, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0},//16: front top left
    { 0.5, 0.5,-0.5, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0},//17: front top right
    { 0.5, 0.5, 0.5, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0},//18: back top right
    {-0.5, 0.5, 0.5, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0},//19: back top left
    //bottom face
    {-0.5,-0.5, 0.5, 0.0,-1.0, 0.0, 1.0, 0.5, 0.0, 1.0},//20: back bottom left
    { 0.5,-0.5, 0.5, 0.0,-1.0, 0.0, 1.0, 0.5, 0.0, 1.0},//21: back bottom right
    { 0.5,-0.5,-0.5, 0.0,-1.0, 0.0, 1.0, 0.5, 0.0, 1.0},//22: front bottom right
    {-0.5,-0.5,-0.5, 0.0,-1.0, 0.0, 1.0, 0.5, 0.0, 1.0} //23: front bottom left
};

const GLubyte indices[36] = {
    //front
    0, 1, 2, 2, 3, 0,
    //left
    4, 5, 6, 6, 7, 4,
    //back
    8, 9, 10, 10, 11, 8,
    //right
    12, 13, 14, 14, 15, 12,
    //top
    16, 17, 18, 18, 19, 16,
    //bottom
    20, 21, 22, 22, 23, 20
};

GLfloat matrix[4][4] = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}
};

Space::Space()
{
    width = 640;
    height = 480;
    aspectRatio = width * (1.0 / height);
    fieldOfView = M_PI / 4;
    zNear = 0.0;
    zFar = 10.0;
    xRot = 0.0;
    yRot = 0.0;
    zRot = 0.0;
    xTrans = 0.0;
    yTrans = 0.0;
    zTrans = 5.0;
    error_code = Init();
}

Space::Space(unsigned int w, unsigned int h)
{
    width = w;
    height = h;
    aspectRatio = width * (1.0 / height);
    fieldOfView = M_PI / 4;
    zNear = -2.0;
    zFar = 2.0;
    xRot = 0.0;
    yRot = 0.0;
    zRot = 0.0;
    xTrans = 0.0;
    yTrans = 0.0;
    zTrans = 5.0;
    error_code = Init();
}

Space::~Space()
{
    Quit();
}

int Space::Init()
{
    GLenum glewError = GLEW_OK;

    if (0 > SDL_Init(SDL_INIT_VIDEO)) {
        std::fprintf(stderr,"SDL_Init failed:\n%s\n", SDL_GetError());
        return 1;
    }

    if (0 > SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE)) {
        return 2;
    }
    if (0 > SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3)) {
        return 2;
    }
    if (0 > SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2)) {
        return 2;
    }
    if (0 > SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1)) {
        return 2;
    }

    display = SDL_CreateWindow(
        "SDL OpenGL",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_OPENGL
    );
    if (NULL == display) {
        std::fprintf(stderr, "SDL_CreateWindow failed:\n%s\n", SDL_GetError());
        return 1;
    }

    context = SDL_GL_CreateContext(display);
    if (NULL == context) {
        std::fprintf(stderr, "SDL_GL_CreateContext failed:\n%s\n", SDL_GetError());
        return 2;
    }

    glewExperimental = GL_TRUE;
    glewError = glewInit();
    if (GLEW_OK != glewError) {
        std::fprintf(stderr, "glewInit failed:\n%s\n", glewGetErrorString(glewError));
    }

    if (0 > SDL_GL_SetSwapInterval(1)) {
        std::fprintf(stderr, "SDL_GL_SetSwapInterval failed:\n%s\n", SDL_GetError());
    }

    glClearColor(0.0f, 0.0f, 0.05f, 0.0f);

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    if (!shader.Init("main.vert", "main.frag")) {
        return 3;
    }

    return 0;
}

unsigned short int Space::HandleEvents()
{
    while (SDL_PollEvent(&event)) {
        if (SDL_QUIT == event.type) {
            return 0;
        } else if (SDL_KEYUP == event.type) {
            if (SDLK_ESCAPE == event.key.keysym.sym) {
                return 0;
            } else if (SDLK_SPACE == event.key.keysym.sym) {
                return 1;
            }
        }
    }
    return -1;
}

void Space::LoadBuffer()
{
    glGenBuffers(1, vertexBuffers);
    glGenBuffers(1, indexBuffers);
    glGenVertexArrays(1, vertexArrays);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, 24 * 10 * sizeof(GLfloat), cube, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLubyte), indices, GL_STATIC_DRAW);

    glBindVertexArray(vertexArrays[0]);

    shader.UseProgram();
}

void Space::Render()
{
    CalculateWorldMatrix();

    shader.Transform(matrix);

    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (const GLvoid*) (6 * sizeof(GLfloat)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[0]);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    SDL_GL_SwapWindow(display);
}

void Space::Quit()
{
    shader.Clean();
	glDeleteBuffers(1, vertexBuffers);
    glDeleteVertexArrays(1, vertexArrays);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(display);
    SDL_Quit();
}

int Space::GetError()
{
    return error_code;
}

void Space::CalculateWorldMatrix()
{
    static float t = 0.0;
    float tanFOV = std::tan(fieldOfView / 2);
    float rtanFOV = aspectRatio * tanFOV;
    float cosX = std::cos(xRot);
    float sinX = std::sin(xRot);
    float cosY = std::cos(yRot);
    float sinY = std::sin(yRot);
    float cosZ = std::cos(zRot);
    float sinZ = std::sin(zRot);
    float dz = zNear - zFar;
    float A = (- zNear - zFar) / dz;
    float B = (2 * zNear * zFar) / dz;

    xRot += 0.04;
    if (2 * M_PI <= xRot) {
        xRot = 0.0;
    }
    yRot += 0.02;
    if (2 * M_PI <= yRot) {
        yRot = 0.0;
    }
    zRot += 0.01;
    if (2 * M_PI <= zRot) {
        zRot = 0.0;
    }

    t += 0.01;
    if (2 * M_PI <= t) {
        t = 0.0;
    }
    xTrans = 0.875 * std::sin(t) + 0.5 * std::cos(6 * t);
    yTrans = 0.875 * std::cos(t) - 0.5 * std::sin(6 * t);

    matrix[0][0] = cosX * cosY / rtanFOV;
    matrix[0][1] = - sinX * cosY / rtanFOV;
    matrix[0][2] = - sinY / rtanFOV;
    matrix[0][3] = xTrans / rtanFOV;

    matrix[1][0] = (sinX * cosZ - cosX * sinY * sinZ) / tanFOV;
    matrix[1][1] = (cosX * cosZ + sinX * sinY * sinZ) / tanFOV;
    matrix[1][2] = - cosY * sinZ / tanFOV;
    matrix[1][3] = yTrans / tanFOV;

    matrix[2][0] = A * (cosX * sinY * cosZ + sinX * sinZ);
    matrix[2][1] = A * (cosX * sinZ - sinX * sinY * cosZ);
    matrix[2][2] = A * cosY * cosZ;
    matrix[2][3] = B + A * zTrans;

    matrix[3][0] = cosX * sinY * cosZ + sinX * sinZ;
    matrix[3][1] = cosX * sinZ - sinX * sinY * cosZ;
    matrix[3][2] = cosY * cosZ;
    matrix[3][3] = zTrans;
}
