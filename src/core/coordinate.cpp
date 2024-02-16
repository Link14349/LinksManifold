#include <iostream>
#include "core/coordinate.h"
#include "core/manifold.h"

void Coordinate::transform(CoordinateSystem* coordinateSystem) {
    if (cs == coordinateSystem->id) return;
    if (!manifold->transform[cs][coordinateSystem->id]) {
        std::cerr << "Coordinate transform undefined" << std::endl;
        exit(1);
    }
    manifold->transform[cs][coordinateSystem->id](value);
    cs = coordinateSystem->id;
}
void Coordinate::transform(int id) {
    if (cs == id) return;
    manifold->transform[0][1](value);
    std::cout << cs << ", " << id << ", " << std::endl;
    if (!manifold->transform[cs][id]) {
        std::cerr << "Coordinate transform undefined" << std::endl;
        exit(1);
    }
    manifold->transform[cs][id](value);
    cs = id;
}