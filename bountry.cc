#include "bountry.h"

Bountry::Bountry() : base(0), length(0) {}

Bountry::Bountry(double b, double l) : base(b), length(l) {
    double h = sqrt(l / (1 + tan_0 * tan_0));
    double x = h * tan_0;

    diameter = sqrt((b - x) * (b - x) + h * h);
    pVector a0(0, 0), b0(-x, h), c0(h, b - x), d0(b, 0);

    bountry = {a0, b0, c0, d0};
}

Bountry::Bountry(double a, double b, int num) : base(a), length(b), diameter(b) {
    double ratio = a / b;
    double cn_1 = pow(ratio, num) - 1;
    double cn_1sq = cn_1 * cn_1;
    pVector right(a, 0), up(0, b);
    bountry = {right, up, right.neg(), up.neg()};
    double cj = 1.0;
    for(int i = 1; i < num; i++) {
        cj = cj * ratio;
        double cj_1 = cj - 1;
        double cj_1sq = cj_1 * cj_1;
        pVector tmp(a * (cn_1sq - cj_1sq) / (cn_1sq + cj_1sq), 2 * b * (cn_1 * cj_1) / (cn_1sq + cj_1sq));
        pVector tmpflip = tmp.flipy();
        bountry.push_back(tmp);
        bountry.push_back(tmp.neg());
        bountry.push_back(tmpflip);
        bountry.push_back(tmpflip.neg());
    }
}

bool Bountry::collision(Bountry B, pVector diff, pVector search) {
    if(diff.length2 > this->diameter * this->diameter + B.diameter * B.diameter) {
        return false;
    }
    shape Bshape;
    for( pVector &p : B.bountry) {
        Bshape.push_back(p + diff);
    }
    Simplex simp;
    simp.add(support(this->bountry, Bshape, search));
    search = search.neg();

    while(true) {
        simp.add(support(this->bountry, Bshape, search));
        if(simp.new_vec.dot(search) <= 0) {
            return false;
        } else {
            if(contain_origin(simp, search)) {
                return true;

            }
        }
    }
}


pVector Bountry::support1(shape a, pVector axis) {
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

pVector Bountry::support(shape a, shape b, pVector axis) {
    return support1(a, axis) - support1(b, axis.neg());
}

bool Bountry::contain_origin(Simplex& s, pVector& d) {
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
