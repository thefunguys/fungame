#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

namespace Draw {
    void triangle(SDL_Renderer* r) {
        filledTrigonRGBA(r, 50, 50, 100, 100, 100, 50, 0x255, 0x0, 0x0, 255U);
    }
}
