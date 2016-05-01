#include <iostream>
#include <vector>
#include <cmath>

struct pVector {
    double x;
    double y;
    double length2;

    pVector() : x(0), y(0), length2(0) {}

    pVector(double a, double b) : x(a), y(b) {
        length2 = a * a + b * b;
    }
    double dot(pVector other) {
        return this->x * other.x + this->y * other.y;
    }
    pVector neg() {
        pVector tmp(-this->x, -this->y);
        return tmp;
    }

    pVector operator+(pVector right) {
        pVector final(this->x + right.x, this->y + right.y);
        return final;
    }

    pVector operator-(pVector right) {
        pVector final(this->x - right.x, this->y - right.y);
        return final;
    }

    pVector flipy() {
        pVector tmp(-this->x, this->y);
        return tmp;
    }

    pVector perp_using(pVector used) {
        pVector final(-this->y, this->x);
        bool neg_orient = (used.x * this->y - used.y * this->x) < 0;
        if(neg_orient) {
            final = final.neg();
        }
        return final;
    }
};

struct Simplex {
    pVector new_vec, one, two;
    int size;

    Simplex() : size(0) {}

    void add(pVector new_vec) {
        if(size == 1) {
            one = this->new_vec;
        } else if(size == 2) {
            two = one;
            one = this->new_vec;
        }
        this->new_vec = new_vec;
        size++;
    }

    void remove(int vName) {
        if(vName == 1) {
            one = two;
        }
        size--;
    }
};

typedef std::vector<pVector> shape;

const double tan_0 = 1.0;

class Bountry {
  public:
    double base, length;
    double diameter;
    shape bountry;

    Bountry();
    Bountry(double, double);
    Bountry(double, double, int);
    bool collision(Bountry, pVector, pVector);
    pVector support1(shape, pVector);
    pVector support(shape, shape, pVector);
    bool contain_origin(Simplex&, pVector&);

};


