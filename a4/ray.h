/*
 * Ray.h
 * Ray class for all your ray casting needs
 *
 * A simple ray consists of a position and direction, as
 * well as some basic functionality that goes with raycasting
 **/

#include "vector.h"
#include "sceneobject.h"

class Ray {
	public:
		Ray(Vector3 position, Vector3 direction) { this->pos=position; direction.normalize(); this->dir=direction; }
		~Ray() {}

		Ray& operator= (Ray const& ray) { this->pos=ray.pos; this->dir=ray.dir; return *this; }
		Ray(Ray const& ray) { this->pos=ray.pos; this->dir=ray.dir; }

		float distance(Vector3 point) {
			return sqrt((point-this->pos).sqlength());
		}

		// check if this ray intersects an object; then set a point/normal/t(distance)
		bool intersect(SceneObject* object, Vector3 &point, Vector3 &normal, float &t) {
			if (object->whatami()=="Plane") {
				// Assume the the plane is short and runs forever (x-inf, z-inf, y=1)
				// pHit: o+td; only hits where o_y + td_y = y
				t=(object->pos.y - this->pos.y)/(float)this->dir.y;
				if (t<=0) return false;

				point = this->pos + this->dir*t;
				normal= Vector3(0,1,0);

				return true;
			} else { // Assumed sphere
				// Sphere intersection explained
				// Sphere: x^2 + y^2 + z^2 = r^2
				// 	if ray intersects sphere then this equation holds
				// 	let O = (ray_pos - obj_center)
				//	(O_x+td_x)^2 + (O_y+td_y)^2 + (O_z+td_z)^2 = r^2
				//	[(O_x*O_x) + 2td_xO_x + t^2(d_x*d_x)] + [(O_y*O_y) + 2td_yO_y + t^2(d_y*d_y)] + [(O_z*O_z) + 2td_zO_z + t^2(d_z*d_z)] = r^2
				//	[(O_x*O_x) + (O_y*O_y) + (O_z*O_z)] + 2t[d_xO_x + d_yO_y + d_zO_z] + t^2[(d_x*d_x) + (d_y*d_y) + (d_z*d_z)] = r^2
				//	|O| + 2t|dO| + t^2|d| = r^2
				//	t^2|d| + 2t|dO| + (|O|-r^2) = 0
				//	t^2 + 2t|dO| + (|O|-r^2) = 0   ; |d| direction vector is normalized
				//
				//	Given that equation, we can solve for t with the quadratic equation
				//	a=1, b=2|dO|, c=(|O|-r^2)
				//	t = (-b +- sqrt(b^2 - 4ac))/2a
				//	t = (-b +- sqrt(b^2 - ac))/a   ; let b=d (divide out the 2)
				//	t = (-dO +- sqrt(dO - (O-r^2)))
				//
				//	let o = ray position, c = object center (expanding O)
				//	t = (-d(o-c)(o-c) +- sqrt(d(o-c)(o-c) - (o-c)(o-c) + r^2))
				//
				//	therefore the hit points are,
				//	t = -d(o-c) + sqrt(dd(o-c)(o-c) - (o-c)(o-c)+r^2)
				//	t = -d(o-c) - sqrt(dd(o-c)(o-c) - (o-c)(o-c)+r^2)
				//
				//  these hits will NOT exist if the results are imaginary
				//  ray MISSES when  
				//   *  d(o-c) < 0
				//   *  (o-c)(o-c) - d(o-c)*d(o-c) > r^2
				Vector3 l = object->pos - this->pos;
				float s = l.dot(this->dir);
				if (s<0) return false; // ray misses sphere (first miss)
				float r = ((SceneSphere*)object)->radius;
				float r2=r*r;
				float m2=l.dot(l)-s*s;
				if (m2>r2) return false;  //a ray misses sphere (second miss)

				// calculate hit position
				float q = sqrt(r2-m2);
				t=s-q;
				if (t<0) t=s+q;
				
				point = this->pos + this->dir*t;
				normal = point - object->pos;
				return true;
			}

			return false;
		}

		Vector3 pos;
		Vector3 dir;
};

