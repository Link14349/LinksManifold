#ifndef __TENSOR_H_
#define __TENSOR_H_

#include <iostream>
#include "coordinate.h"
#include <stdarg.h>

// pow实现....
template <int m, int n>
class __pow {
public:
    static constexpr int res = __pow<m, n - 1>::res * m;
};
template <int m>
class __pow<m, 0> {
public:
    static constexpr int res = 1;
};
// pow实现end...

class Manifold;

template <int k, int l>
class Array {
public:
    static constexpr int ARRLEN = __pow<N, k + l>::res;
    Array() {
        for (int i = 0; i < ARRLEN; i++) arr[i] = 0;
    }
    Array(const Array& array) {
        for (int i = 0; i < ARRLEN; i++) arr[i] = array.arr[i];
    }
    const Array<k, l>& operator=(const Array<k, l>& arr) {
        for (int i = 0; i < ARRLEN; i++) arr[i] = arr.arr[i];
    }
    inline void fillZero() {
        for (int i = 0; i < ARRLEN; i++) arr[i] = 0.0;
    }
    inline double& at(std::initializer_list<int> super, std::initializer_list<int> sub) {
        int idx = 0;
        if (super.size() != k || sub.size() != l) {
            std::cerr << "Wrong array initialization length" << std::endl;
            exit(1);
        }
        for (int i : super) idx = idx * N + i;
        for (int i : sub) idx = idx * N + i;
        return arr[idx];
    }
    double arr[ARRLEN];
};

// contraction a1^...a a2_...b
// template <int k1, int l1, int k2, int l2, int a1n, int a2n>// a1n: a1n中上角标缩并数量, 
// Array<k1 + k2 - a1n - a2n, l1 + l2 - a1n - a2n> contraction(const Array<k1, l1>& a1, const Array<k2, l2>& a2, int super1[a1n], int super2[a2n]) {
//     Array<k1 + k2 - a1n - a2n, l1 + l2 - a1n - a2n> res;
    
//     return res;
// }

// Define (k, l) Tensor
template <int k, int l>
class Tensor {
private:
    Manifold* manifold;
public:
    Coordinate coord;
    Array<k, l> array;
    Tensor(Manifold* m, Coordinate c) : manifold(m), array(), coord(c) { }
    Tensor(Manifold* m, const Array<k, l>& arr, Coordinate c) : manifold(m), array(arr), coord(c) { }
    Tensor(const Tensor<k, l>& tensor) : manifold(tensor.manifold), array(tensor.array), coord(tensor.coord) { }
    void transform(int id);
    inline double& at(std::initializer_list<int> super, std::initializer_list<int> sub) {
        return array.at(super, sub);
    }
};

// Define (k, l) Tensor field
template <int k, int l>
class TensorField {
private:
    Manifold* manifold;
    void (*funcs[COORDINATE_CAPABILITY]) (Coordinate&, Array<k, l>*);// Define components in different coordinates
public:
    TensorField(Manifold* m) : manifold(m) {
        for (int i = 0; i < COORDINATE_CAPABILITY; i++) funcs[i] = nullptr;
    }
    void value(Coordinate&& coord, Tensor<k, l>* tensor) {
        if (!funcs[coord.cs]) {
            std::cerr << "Undefined coordinate id in tensor." << std::endl;
            exit(1);
        }
        tensor.coord = coord;
        funcs[coord.cs](coord, &tensor.array);
    }
    Tensor<k, l> value(Coordinate&& coord) {
        if (!funcs[coord.cs]) {
            std::cerr << "Undefined coordinate id in tensor." << std::endl;
            exit(1);
        }
        Tensor<k, l> tensor(manifold, coord);
        funcs[coord.cs](coord, &tensor.array);
        return tensor;
    }
    void addFunc(CoordinateSystem* cs, void (*func) (Coordinate&, Array<k, l>*)) {
        funcs[cs->id] = func;
    }
};

using Scalar = Tensor<0, 0>;
using Vector = Tensor<1, 0>;
using DVector = Tensor<0, 1>;
using ScalarField = TensorField<0, 0>;
using VectorField = TensorField<1, 0>;
using DVectorField = TensorField<0, 1>;

#endif