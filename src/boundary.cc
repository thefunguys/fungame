#include "boundary.h"

Boundary::Boundary() : base(0), length(0) {}

Boundary::Boundary(double full_b, double b, double l) : base(b), length(l) {
    // double h = sqrt(l / (1 + tan_0 * tan_0));
    // double x = h * tan_0;

    // diameter = sqrt((b - x) * (b - x) + h * h);
    // pVector a0(0, 0), b0(-x, h), c0(h, b - x), d0(b, 0);
    double off_b = (full_b - b) * .5;
    pVector a0(off_b - 3, 0), b0(off_b + 3, l), c0(off_b + b + 3, l), d0(off_b + b - 3, 0);
    diameter = sqrt(l * l + b * b);
    boundary = {a0, b0, c0, d0};
}

// Boundary::Boundary(double a, double b, int num) : base(a), length(b), diameter(b) {
//     double ratio = a / b;
//     double cn_1 = pow(ratio, num) - 1;
//     double cn_1sq = cn_1 * cn_1;
//     pVector right(a, 0), up(0, b);
//     boundary = {right, up, right.neg(), up.neg()};
//     double cj = 1.0;
//     for(int i = 1; i < num; i++) {
//         cj = cj * ratio;
//         double cj_1 = cj - 1;
//         double cj_1sq = cj_1 * cj_1;
//         pVector tmp(a * (cn_1sq - cj_1sq) / (cn_1sq + cj_1sq), 2 * b * (cn_1 * cj_1) / (cn_1sq + cj_1sq));
//         pVector tmpflip = tmp.flipy();
//         boundary.push_back(tmp);
//         boundary.push_back(tmp.neg());
//         boundary.push_back(tmpflip);
//         boundary.push_back(tmpflip.neg());
//     }
// }

bool Boundary::collision(Boundary B, pVector diff, pVector search) {
    if(diff.length2 > this->diameter * this->diameter + B.diameter * B.diameter) {
        return false;
    }
    shape Bshape;
    for( pVector &p : B.boundary) {
        Bshape.push_back(p + diff);
    }
    Simplex simp;
    simp.add(support(this->boundary, Bshape, search));
    search = search.neg();

    while(true) {
        simp.add(support(this->boundary, Bshape, search));
        if(simp.new_vec.dot(search) <= 0) {
            return false;
        } else {
            if(contain_origin(simp, search)) {
                return true;

            }
        }
    }
}


pVector Boundary::support1(shape a, pVector axis) {
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

pVector Boundary::support(shape a, shape b, pVector axis) {
    return support1(a, axis) - support1(b, axis.neg());
}

bool Boundary::contain_origin(Simplex& s, pVector& d) {
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
