#ifndef __COORDINATE_H_
#define __COORDINATE_H_

#include <iostream>

class Manifold;
class CoordinateSystem;

class Coordinate {
public:
    Coordinate(Manifold* m, int id, double x, double y, double z) : cs(id), manifold(m) {
        value[0] = x;
        value[1] = y;
        value[2] = z;
    }
    Coordinate(const Coordinate& coordinate) : cs(coordinate.cs), manifold(coordinate.manifold) {
        value[0] = coordinate.value[0];
        value[1] = coordinate.value[1];
        value[2] = coordinate.value[2];
    }
    const Coordinate& operator=(const Coordinate& coord) {
        if (manifold != coord.manifold) {
            std::cerr << "Wrong manifold in operator= of Coordinate" << std::endl;
            exit(1);
        }
        cs = coord.cs;
        for (int i = 0; i < 3; i++) value[i] = coord.value[i];
    }
    // switch to coordinate B
    void transform(CoordinateSystem* coordinateSystem);
    void transform(int id);
    Manifold* manifold;
    int cs;// cs id
    double value[3];
    inline double& operator[](int n) {
        return value[n];
    }
};
// Three Dimensional Coordinate
class CoordinateSystem {
public:
    const int id;
    const char* brief;
    CoordinateSystem(Manifold* m, int i, const char* b) : id(i), brief(b), manifold(m) { }
    Coordinate coord(double x, double y, double z) {
        return Coordinate(manifold, id, x, y, z);
    }
private:
    Manifold* manifold;
};

#endif