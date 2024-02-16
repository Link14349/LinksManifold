#include "renderer/renderer.h"
#include "renderer/ray.h"

Camera::Camera(Renderer* r, const Coordinate& c, const Vector& dx, const Vector& dy) : manifold(renderer->manifold), coord(c), dirx(dx), diry(dy), renderer(r) {
}

void Camera::render(bmp::Bitmap& image) {
}

void Renderer::render(bmp::Bitmap& image) {
    camera->render(image);
}