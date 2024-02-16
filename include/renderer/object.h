#ifndef __OBJECT_H_
#define __OBJECT_H_

#include <cmath>
#include "core/manifold.h"

class Object {
public:
    Object(Manifold* m, const Coordinate& coordinate) : m(manifold), coord(coordinate) { }
    virtual bool hit(const Coordinate&) const;
private:
    Manifold* manifold;
    Coordinate coord; 
};

class Point : public Object {
public:
    static double dis(double v1[3], double v2[3]) {
        double s = 0;
        for (int i = 0; i < 3; i++) s += pow(v1[i] - v2[i], 2);
        return sqrt(s);
    }
    Point(manifold* m, const Coordinate& coordinate) : Object(m, coordinate) {}
    bool hit(const Coordinate& c) const {
        c.transform(coord.id);
        if (dis(coord.value, c.value) < 0.001) return true;
        return false;
    }
private:
};

#endif