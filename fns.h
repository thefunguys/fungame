#ifndef FNS_H
#define FNS_H

#include <SDL2/SDL_opengl.h>

#define EPS 0.005

// grumble grumble floating point approxamation
inline bool close_to_zero(double n) {
    return n <= EPS && n >= -EPS;
}

void DrawTriangle() {
    glLoadIdentity();

    glBegin(GL_TRIANGLES);
      glColor3f(1.0, 0.0, 0.0);
      glVertex3f(-0.6f, -0.4f, 0.f);
      glColor3f(0.0, 1.0, 0.0);
      glVertex3f(0.6f, -0.4f, 0.f);
      glColor3f(0.0, 0.0, 1.0);
      glVertex3f(0.f, 0.6f, 0.f);
    glEnd();
}

#endif
