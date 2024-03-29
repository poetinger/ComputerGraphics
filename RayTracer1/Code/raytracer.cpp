#include "raytracer.h"

#include "image.h"
#include "light.h"
#include "material.h"
#include "triple.h"

// =============================================================================
// -- Include all your shapes here ---------------------------------------------
// =============================================================================

#include "shapes/mesh.h"
#include "shapes/plane.h"
#include "shapes/sphere.h"
#include "shapes/triangle.h"
#include "shapes/cylinder.h"

// =============================================================================
// -- End of shape includes ----------------------------------------------------
// =============================================================================

#include "json/json.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <string>

using namespace std; // no std:: required
using json = nlohmann::json;

bool Raytracer::parseObjectNode(json const &node) {
  ObjectPtr obj = nullptr;

  // =============================================================================
  // -- Determine type and parse object parameters
  // ------------------------------
  // -- For each object, load it's data members
  // =============================================================================

  if (node["type"] == "sphere") {
    Point pos(node["position"]);
    double radius = node["radius"];
    obj = ObjectPtr(new Sphere(pos, radius));
  } else if (node["type"] == "triangle") {
    Point vertex1(node["vertices"][0]);
    Point vertex2(node["vertices"][1]);
    Point vertex3(node["vertices"][2]);
    obj = ObjectPtr(new Triangle(vertex1, vertex2, vertex3));
  } else if (node["type"] == "mesh") {
    std::string filename = node["model"];
    Vector translation(node["position"]);
    double scale = node["scale"];
    obj = ObjectPtr(new Mesh(filename, translation, scale));
  } else if (node["type"] == "plane") {
    Point point(node["point"]);
    Vector N(node["normal"]);
    obj = ObjectPtr(new Plane(point, N));
  } else if (node["type"] == "cylinder"){
    Point pointA(node["pointA"]);
    Point pointB(node["pointB"]);
    double radius = node["radius"];
    obj = ObjectPtr(new Cylinder(pointA, pointB, radius));
  } else {
    cerr << "Unknown object type: " << node["type"] << ".\n";
  }

  // =============================================================================
  // -- End of object reading
  // ----------------------------------------------------
  // =============================================================================

  if (!obj)
    return false;

  // Parse material and add object to the scene
  obj->material = parseMaterialNode(node["material"]);
  scene.addObject(obj);
  return true;
}

Light Raytracer::parseLightNode(json const &node) const {
  Point pos(node["position"]);
  Color col(node["color"]);
  return Light(pos, col);
}

Material Raytracer::parseMaterialNode(json const &node) const {
  Color color(node["color"]);
  double ka = node["ka"];
  double kd = node["kd"];
  double ks = node["ks"];
  double n = node["n"];
  return Material(color, ka, kd, ks, n);
}

bool Raytracer::readScene(string const &ifname) try {
  // Read and parse input json file
  ifstream infile(ifname);
  if (!infile)
    throw runtime_error("Could not open input file for reading.");
  json jsonscene;
  infile >> jsonscene;

  // =============================================================================
  // -- Read your scene data in this section
  // -------------------------------------
  // =============================================================================

  Point eye(jsonscene["Eye"]);
  scene.setEye(eye);

  // TODO: add your other configuration settings here

  for (auto const &lightNode : jsonscene["Lights"])
    scene.addLight(parseLightNode(lightNode));

  unsigned objCount = 0;
  for (auto const &objectNode : jsonscene["Objects"])
    if (parseObjectNode(objectNode))
      ++objCount;

  cout << "Parsed " << objCount << " objects.\n";

  // =============================================================================
  // -- End of scene data reading
  // ------------------------------------------------
  // =============================================================================

  return true;
} catch (exception const &ex) {
  cerr << ex.what() << '\n';
  return false;
}

void Raytracer::renderToFile(string const &ofname) {
  // TODO: the size may be a settings in your file
  Image img(400, 400);
  cout << "Tracing...\n";
  scene.render(img);
  cout << "Writing image to " << ofname << "...\n";
  img.write_png(ofname);
  cout << "Done.\n";
}
