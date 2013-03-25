/*
 * Scene.h
 * Scene manager for raytracer
 *
 * Scene manager contains all mesh objects within the scene,
 * loads and interprets a given scenefile and is able to
 * raytrace the scene into a .png image
 **/

#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <exception>
#include <cmath>

#include "fileparse.cpp"
#include "sceneobject.h"
#include "ray.h"

#define PI 3.14159
#define DEBUG false

using namespace std;

class Scene {
public:
	
	Scene(string);
	~Scene();
	void raytrace(int);

private:
	string scenefile; // scenefile to be used

	// Scene stuff
	int dimx, dimy; // dimensions
	float fov; // horizontal/vertical fov in degrees
	Vector3 background;

	void parse();
	Ray computeRay(int,int); // create a ray given the pixel screen coordinates
	Vector3 Trace(Ray ray, int depth); // trace a given ray and return the colour
	float mix(float a, float b, float mix) { return b*mix + a*(1-mix); }

	int max_rays;
	vector <SceneObject*> scene_objects; // all objects within the scene
};

