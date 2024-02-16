#include <iostream>
#include <cmath>
#include "core/manifold.h"
#include "renderer/renderer.h"
#include "BitmapPlusPlus.hpp"
#include <cmath>

void metric0(Coordinate& coord, Array<0, 2>* arr) {
    arr->fillZero();
    arr->at({}, {0, 0}) = 1;
    arr->at({}, {1, 1}) = pow(sin(coord[0]), 2);
    arr->at({}, {2, 2}) = pow(sin(coord[0]), 2) * pow(sin(coord[1]), 2);
}
void christoffel0(Coordinate& coord, Array<1, 2>* arr) {
    arr->fillZero();
    float x = coord.value[0], y = coord.value[1], z = coord.value[2];
    arr->at({0}, {1, 1}) = -sin(x)*cos(x);
    arr->at({0}, {2, 2}) = -sin(x)*pow(sin(y), 2)*cos(x);
    arr->at({1}, {0, 1}) = cos(x)/sin(x);
    arr->at({1}, {1, 0}) = cos(x)/sin(x);
    arr->at({1}, {2, 2}) = -sin(y)*cos(y);
    arr->at({2}, {0, 2}) = cos(x)/sin(x);
    arr->at({2}, {1, 2}) = cos(y)/sin(y);
    arr->at({2}, {2, 0}) = cos(x)/sin(x);
    arr->at({2}, {2, 1}) = cos(y)/sin(y);
}
void metric1(Coordinate& coord, Array<0, 2>* arr) {
    arr->fillZero();
    arr->at({}, {0, 0}) = 1;
    arr->at({}, {1, 1}) = pow(cos(coord[0]), 2);
    arr->at({}, {2, 2}) = pow(cos(coord[0]), 2) * pow(cos(coord[1]), 2);
}
void christoffel1(Coordinate& coord, Array<1, 2>* arr) {
    arr->fillZero();
    float x = coord.value[0], y = coord.value[1], z = coord.value[2];
    arr->at({0}, {1, 1}) = sin(x)*cos(x);
    arr->at({0}, {2, 2}) = sin(x)*cos(x)*pow(cos(y), 2);
    arr->at({1}, {0, 1}) = -sin(x)/cos(x);
    arr->at({1}, {1, 0}) = -sin(x)/cos(x);
    arr->at({1}, {2, 2}) = sin(y)*cos(y);
    arr->at({2}, {0, 2}) = -sin(x)/cos(x);
    arr->at({2}, {1, 2}) = -sin(y)/cos(y);
    arr->at({2}, {2, 0}) = -sin(x)/cos(x);
    arr->at({2}, {2, 1}) = -sin(y)/cos(y);
}
void trans(double coord[3]) {
    coord[0] = M_PI / 2 - coord[0];
    coord[1] = M_PI / 2 - coord[1];
    coord[2] = M_PI / 2 - coord[2];
}
void jacobi(Coordinate& coord, Array<1, 1>* arr) {
    arr->fillZero();
    for (int i = 0; i < 3; i++) arr->at({i}, {i}) = -1;
}

int main() {
    Manifold m;
    m.addCoordinate("HypersphericalCS0");
    m.addCoordinate("HypersphericalCS1");
    m.g.addFunc(m.css[0], metric0);
    m.christoffel.addFunc(m.css[0], christoffel0);
    m.g.addFunc(m.css[1], metric1);
    m.christoffel.addFunc(m.css[1], christoffel1);
    m.transform[0][1] = trans;
    m.transform[1][0] = trans;
    m.jacobi[0][1] = jacobi;
    m.jacobi[1][0] = jacobi;
    
    // Tensor<0, 2> g(m.g.value(m.css[0]->coord(M_PI_2, M_PI_2, M_PI_2)));
    // Tensor<1, 2> gamma(m.christoffel.value(m.css[0]->coord(M_PI_2, M_PI_2, M_PI_2)));
    // g.transform(1);

    // Renderer renderer(&m);
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         std::cout << g.at({}, {i, j}) << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         for (int k = 0; k < 3; k++)
    //             std::cout << gamma.at({i}, {j, k}) << " ";
    //         std::cout << ";\t";
    //     }
    //     std::cout << std::endl;
    // }
    // bmp::Bitmap image(1280, 960);

    // for (std::int32_t y = 0; y < image.height(); ++y) {
    //     for (std::int32_t x = 0; x < image.width(); ++x) {
    //         image.set(x, y, { 255 * x / image.width(), 255 * y / image.height(), 0 });
    //     }
    // }

    // image.save("testout.bmp");
    return 0;
}

/*
Γ^0_11: -sin(x)*cos(x)
Γ^0_22: -sin(x)*sin(y)**2*cos(x)
Γ^1_01: cos(x)/sin(x)
Γ^1_10: cos(x)/sin(x)
Γ^1_22: -sin(y)*cos(y)
Γ^2_02: cos(x)/sin(x)
Γ^2_12: cos(y)/sin(y)
Γ^2_20: cos(x)/sin(x)
Γ^2_21: cos(y)/sin(y)
*/