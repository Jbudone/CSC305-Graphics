/*
 * SceneObject.h
 * Base class for an object in the scene
 *
 * All objects within the scene (lights, floor, spheres) are
 * derived off of the SceneObject
 **/
#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H


#include "vector.h"

class SceneObject {
	public:
		SceneObject(float x, float y, float z,
					float r, float g, float b,
					char material)
			: pos(x,y,z), col(r,g,b), reflective(false), transparent(false) {

				light=Vector3(0,0,0);
				if (material=='R') reflective=true; 
				else if (material=='T') transparent=true;
		}
		Vector3 pos;
		Vector3 col;
		Vector3 light;
		virtual string whatami()=0;
		bool reflective;
		bool transparent;
};

class ScenePlane: public SceneObject {
	public:
		ScenePlane(float x, float y, float z,
					float r, float g, float b,
					char material)
			: SceneObject(x,y,z,r,g,b,material) {

		}

		string whatami() { return "Plane"; }
};

class SceneSphere: public SceneObject {
	public:
		SceneSphere(float x, float y, float z,
					float r, float g, float b,
					float radius, char material)
			: SceneObject(x,y,z,r,g,b,material) {
				this->radius=radius;
		}

		string whatami() { return "Sphere"; }
		float radius;
};


class SceneLight: public SceneSphere {
	public:
		SceneLight(float x, float y, float z,
					float r, float g, float b,
					float radius,
					float intensity)
			: SceneSphere(x,y,z,0,0,0,radius,' ') {
				this->intensity=intensity;
				this->light=Vector3(intensity,intensity,intensity);
		}

		string whatami() { return "Light"; }
		float intensity;
};

#endif
