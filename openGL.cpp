#include <cstdio>
#include <ctime>

#include "space.h"

int main(int argc, char** argv)
{
    unsigned int WIDTH = 800;
    unsigned int HEIGHT = 600;
    bool running = true;
    clock_t clockCounter;
    Space space(WIDTH, HEIGHT);

    if (0 != space.GetError()) {
        return 1;
    }

    space.LoadBuffer();

    while (running) {
        clockCounter = clock();
        running = space.HandleEvents();

        space.Render();

        while (CLOCKS_PER_SEC / 60.0 > clock() - clockCounter) {}

        fprintf(
            stdout,
            "%.2g \r",
            ((float) CLOCKS_PER_SEC) / (clock() - clockCounter)
        );
        fflush(stdout);
    }

    return 0;
}
