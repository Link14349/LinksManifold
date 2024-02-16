#ifndef __RENDERER_H_
#define __RENDERER_H_

#include <vector>
#include "core/manifold.h"
#include "core/coordinate.h"
#include "BitmapPlusPlus.hpp"
#include "object.h"
using std::vector;

class Renderer;

class Camera {
private:
    Manifold* manifold;
    Coordinate coord;
    Vector dirx, diry;
    Renderer* renderer;
public:
    Camera(Renderer* r, const Coordinate& c, const Vector& dx, const Vector& dy);
    void render(bmp::Bitmap& image);
};

class Renderer {
public:
    friend class Camera;
    Renderer(Manifold* m) : manifold(m) { }
    void setCamera(Camera* c) {
        camera = c;
    }
    void render(bmp::Bitmap& image);
    vector<Object*> objs;
private:
    Manifold* manifold;
    Camera* camera;
};

#endif