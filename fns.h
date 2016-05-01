#ifndef FNS_H
#define FNS_H

#include <SDL2/SDL_opengl.h>

#define EPS 0.005

// grumble grumble floating point approxamation
inline bool close_to_zero(double n) {
    return n <= EPS && n >= -EPS;
}


#endif
