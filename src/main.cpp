#include "renderer.h"

int main(int argc, char **argv) {
    Renderer renderer;

    if (!renderer.initImGui()) return 1;
    renderer.loopRender();

    return 0;
}
