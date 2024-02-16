#ifndef __RAY_H_
#define __RAY_H_

#include "core/coordinate.h"
#include "core/tensor.h"

class Ray {
public:
    Coordinate coord;
    Vector direction;
};


#endif