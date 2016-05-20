#ifndef FNS_H
#define FNS_H

#define EPS 0.005

// grumble grumble floating point approxamation
inline bool close_to_zero(double n) {
    return n <= EPS && n >= -EPS;
}


#endif
