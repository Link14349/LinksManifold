#ifndef __MANIFOLD__H_
#define __MANIFOLD__H_

#define N 3
#define COORDINATE_CAPABILITY 16

#include "coordinate.h"
#include "tensor.h"

class Manifold {
private:
    int cslen = 0;
public:
    CoordinateSystem* css[COORDINATE_CAPABILITY];// Maximum capability: 16
    void (*transform[COORDINATE_CAPABILITY][COORDINATE_CAPABILITY]) (double[3]);// transform[A][B] switch coordinate (x, y, z) in A to B
    void (*jacobi[COORDINATE_CAPABILITY][COORDINATE_CAPABILITY]) (Coordinate&, Array<1, 1>*);// Jacobi A->B: arr^i_j=∂x_B^i/∂x_A^j
    TensorField<0, 2> g;
    TensorField<1, 2> christoffel;// Christoffel Symbol
    Manifold() : g(this), christoffel(this) {
        for (int i = 0; i < COORDINATE_CAPABILITY; i++) {
            css[i] = nullptr;
            for (int j = 0; j < COORDINATE_CAPABILITY; j++) {
                transform[i][j] = nullptr;
                jacobi[i][j] = nullptr;
            }
        }
    }
    CoordinateSystem* cs(int idx) const { return css[idx]; }
    void addCoordinate(const char* brief) { 
        css[cslen] = new CoordinateSystem(this, cslen, brief);
        cslen++;
    }
    ~Manifold() {
        for (int i = 0; i < cslen; i++) delete css[i];
    }
};

#include <iostream>

template <int k, int l>
void Tensor<k, l>::transform(int id) {
    if (id == coord.cs) return;
    if (!manifold->jacobi[coord.cs][id]) {
        std::cerr << "Coordinate transform undefined" << std::endl;
        exit(1);
    }
    Array<k, l> tmp(array);
    Array<1, 1> jacobi1;
    Array<1, 1> jacobi2;
    manifold->jacobi[coord.cs][id](coord, &jacobi1);
    manifold->jacobi[id][coord.cs](coord, &jacobi2);
    for (int i = 0; i < Array<k, l>::ARRLEN; i++) {
        array.arr[i] = 0;
        for (int j = 0; j < Array<k, l>::ARRLEN; j++) {
            double factor = 1;
            int i_ = i, j_ = j;
            // encode j
            for (int a = 0; a < l; a++) {
                factor *= jacobi2.at({j_ % 3}, {i_ % 3});
                i_ /= 3, j_ /= 3;
            }
            for (int a = 0; a < k; a++) {
                factor *= jacobi1.at({i_ % 3}, {j_ % 3});
                i_ /= 3, j_ /= 3;
            }
            array.arr[i] += factor * tmp.arr[j];
        }
    }
    coord.transform(id);
}

#endif