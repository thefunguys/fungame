#include <iostream>
#include <vector>

struct pVector {
    int x;
    int y;
    int length2;

    pVector() : x(0), y(0), length2(0) {}

    pVector(int a, int b) : x(a), y(b) {
        length2 = a*a + b*b;
    }
    double dot(pVector other) {
        return this->x*other.x + this->y*other.y;
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

    pVector perp_using(pVector used) {
        pVector final(-this->y,this->x);
        bool neg_orient = (used.x*this->y - used.y*this->x) < 0;
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
        } else if( vName == 2) {

        }
        size--;
    }
};

typedef std::vector<pVector> shape;

pVector support1(shape, pVector);
pVector support(shape, shape, pVector);
bool contain_origin(Simplex&, pVector&);
bool collision(shape, shape, pVector);



pVector support1(shape a, pVector axis) {
    pVector support_vec = a[0];
    double largest = support_vec.dot(axis);

    for( pVector &p : a) {
        double temp = p.dot(axis);
        if ( temp > largest) {
            largest = temp;
            support_vec = p;
        }
    }
    return support_vec;
}

pVector support(shape a, shape b, pVector axis) {
    return support1(a, axis) - support1(b, axis.neg());
}


bool collision(shape A, shape B, pVector search) {
    Simplex simp;
    simp.add(support(A, B, search));
    search = search.neg();

    while(true) {
        simp.add(support(A,B,search));
        if(simp.new_vec.dot(search) <= 0) {
            return false;
        } else {
            if(contain_origin(simp, search)) {
                return true;

            }
        }
    }
}

bool contain_origin(Simplex& s, pVector& d) {
    pVector a = s.new_vec;

    if(s.size == 3) {
        pVector ab = s.one - a;
        pVector ac = s.two - a;

        pVector abPerp = ab.perp_using(ac);
        pVector acPerp = ac.perp_using(ab);

        if(abPerp.dot(a) < 0) {
            s.remove(2);
            d = abPerp;
        } else if(acPerp.dot(a) < 0 ) {
            s.remove(1);
            d = acPerp;
        } else {
            return true;
        }
    } else {
        pVector ab = s.one - a;
        pVector abPerp = ab.perp_using(a);

        d = abPerp;
    }
    return false;
}
