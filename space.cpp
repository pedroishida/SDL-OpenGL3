#include "space.h"

const GLfloat triangle[3][7] = {
    {0.5, -0.5, 0.0, 1.0, 0.0, 0.0, 1.0},
    {-0.5, -0.5, 0.0, 0.0, 1.0, 0.0, 1.0},
    {0.0, 0.5, 0.0, 0.0, 0.0, 1.0, 1.0}
};

Space::Space()
{
    width = 640;
    height = 480;
    error_code = Init();
}

Space::Space(unsigned int w, unsigned int h)
{
    width = w;
    height = h;
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
    glGenVertexArrays(1, vertexArrays);

    glBindVertexArray(vertexArrays[0]);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * 7 * sizeof(GLfloat), triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (const GLvoid*) (3 * sizeof(GLfloat)));

    shader.UseProgram();
}

void Space::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 3);

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
