#include "scene.h"

#include "hit.h"
#include "image.h"
#include "material.h"
#include "ray.h"

#include <cmath>
#include <limits>

using namespace std;

Color Scene::trace(Ray const &ray) {
  // Find hit object and distance
  Hit min_hit(numeric_limits<double>::infinity(), Vector());
  ObjectPtr obj = nullptr;
  for (unsigned idx = 0; idx != objects.size(); ++idx) {
    Hit hit(objects[idx]->intersect(ray));
    if (hit.t < min_hit.t) {
      min_hit = hit;
      obj = objects[idx];
    }
  }

  // No hit? Return background color.
  if (!obj)
    return Color(0.0, 0.0, 0.0);

  Material material = obj->material; // the hit objects material
  Point hit = ray.at(min_hit.t);     // the hit point
  Vector N = min_hit.N;              // the normal at hit point
  Vector V = -ray.D;                 // the view vector

  /****************************************************
   * This is where you should insert the color
   * calculation (Phong model).
   *
   * Given: material, hit, N, V, lights[]
   * Sought: color
   *
   * Hints: (see triple.h)
   *        Triple.dot(Vector) dot product
   *        Vector + Vector    vector sum
   *        Vector - Vector    vector difference
   *        Point - Point      yields vector
   *        Vector.normalize() normalizes vector, returns length
   *        double * Color     scales each color component (r,g,b)
   *        Color * Color      dito
   *        pow(a,b)           a to the power of b
   ****************************************************/

  Vector NHat = N.normalized(); // Normalized N
  Vector VHat = V.normalized(); // Normalized V

  // We add an extra scale factor for us to universally adjust if needed
  const float AMBIENT_LIGHT_INTENSITY = 1.0;

  Color color = material.ka * AMBIENT_LIGHT_INTENSITY * material.color;

  for (auto lightPtr : lights) {
    Vector L = (lightPtr->position - hit).normalized();

    // Diffuse term
    float NdotL = NHat.dot(L);
    float intensity = max(min(NdotL, 1.0f), 0.0f);
    color += material.kd * intensity * material.color * (lightPtr->color);

    // Specular term
    Vector R = (2 * (NdotL)*NHat - L).normalized();
    float VdotR = VHat.dot(R);
    intensity = pow(max(min(VdotR, 1.0f), 0.0f), material.n);
    color += material.ks * intensity * (lightPtr->color);
  }

  return color;
}

void Scene::render(Image &img) {
  unsigned w = img.width();
  unsigned h = img.height();

#pragma omp parallel for
  for (unsigned y = 0; y < h; ++y) {
    for (unsigned x = 0; x < w; ++x) {
      Point pixel(x + 0.5, h - 1 - y + 0.5, 0);
      Ray ray(eye, (pixel - eye).normalized());
      Color col = trace(ray);
      col.clamp();
      img(x, y) = col;
    }
  }
}

// --- Misc functions ----------------------------------------------------------

void Scene::addObject(ObjectPtr obj) { objects.push_back(obj); }

void Scene::addLight(Light const &light) {
  lights.push_back(LightPtr(new Light(light)));
}

void Scene::setEye(Triple const &position) { eye = position; }

unsigned Scene::getNumObject() { return objects.size(); }

unsigned Scene::getNumLights() { return lights.size(); }
