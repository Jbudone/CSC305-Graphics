#include "scene.h"


Scene::Scene(string scenefile) {

	// Does file exist?
	struct stat null_placeholder;
	if (stat(scenefile.c_str(), &null_placeholder)<0) {
		printf("ERROR: Could not find file %s\n",scenefile.c_str());
		throw exception();
	}
	this->scenefile=scenefile;

	parse(); // parse the scenefile
	fov=tan(fov*PI/((float)180*2)); // convert to fov angle (in rad)
}

Scene::~Scene() {

}

void Scene::parse() {
	FILE *file = NULL;
	char buf[1024];

	// open file for reading
	file = fopen(scenefile.c_str(),"r");
	if (file == NULL) {
		printf("Error reading file %s\n",scenefile.c_str());
		throw exception();
	}

	// read meshes from scenefile
	float x, y, z, r, g, b, i, i2; // Inputs <position>, <colour>, [intensity|radius]
	char m; // material
	string line, token;
	while (true) {
		memset(buf,0,sizeof(buf));
		if (!fgets(buf, 1024, file)) break;

		// trim and parse line
		line=trim(buf);
		token=getToken(line);
		if (line.empty()) continue;
#if DEBUG
		printf("Trimmed: %s\n",line.c_str());
		printf("Token: %s\n",token.c_str());
#endif
		if (token=="floor") {
			// <position> <colour> [material]
			sscanf(line.c_str(), "%s %f %f %f %f %f %f %c", buf, &x, &y, &z, &r, &g, &b, &m);
			scene_objects.push_back(new ScenePlane(x,y,z,r,g,b,m));
		} else if (token=="light") {
			// <position> <colour> [radius] [intensity]
			sscanf(line.c_str(), "%s %f %f %f %f %f %f %f %f", buf, &x, &y, &z, &r, &g, &b, &i, &i2);
			scene_objects.push_back(new SceneLight(x,y,z,r,g,b,i,i2));
		} else if (token=="sphere") {
			// <position> <colour> [radius] [material]
			sscanf(line.c_str(), "%s %f %f %f %f %f %f %f %c", buf, &x, &y, &z, &r, &g, &b, &i, &m);
			scene_objects.push_back(new SceneSphere(x,y,z,r,g,b,i,m));
		} else if (token=="scene") {
			// [width] [height] [fov] <background>
			sscanf(line.c_str(), "%s %f %f %f %f %f %f", buf, &x, &y, &i, &r, &g, &b);
			dimx=x; dimy=y; fov=i;
			background=Vector3(r,g,b);
		} else {
			printf("Unknown token detected: %s\n",token.c_str());
		}
	}
}


Ray Scene::computeRay(int x, int y) {
	// Create a ray based on the current FOV view frustum
	float ratio = dimx/(float)dimy;


	// project coordinates into screen-space [-1,1]
	x+=0.5; y+=0.5; // use the mid-section of pixel
	float xw=(x/(float)dimx)*2-1;
	float yw=(y/(float)dimy)*2-1;
	yw*=-1; // y flipped

	// project coordinates into world-space (fov)
	xw*=fov*ratio;
	yw*=fov;

	// Ray cast out from (0,0,0), outwards in the direction of xw,yw and -1 outwards
	// NOTE: Ray automatically normalizes direction vector
	return Ray(Vector3(0,0,0), Vector3(xw, yw, -1));
}

void Scene::raytrace(int num_rays) {
	// Go through every pixel to cast a ray and retrieve the colour, then write it to a .ppm file
	
	max_rays=num_rays;

#if DEFINE
	// Be friendly to the user; let them know what scene objects were loaded
	for (int i=0; i<scene_objects.size(); i++) {
		printf("Scene Object: %s\n", scene_objects[i]->whatami().c_str());
	}
#endif

	/** the following snippet has been shamelessly
	 * stolen from: http://rosettacode.org/wiki/Bitmap/Write_a_PPM_file#C **/
	int i, j;
	FILE *fp = fopen("first.ppm", "wb"); /* b - binary mode */
	(void) fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
	for (j = 0; j < dimy; ++j) {
		for (i = 0; i < dimx; ++i) {
		  static unsigned char pixel[3];

		  Ray ray = computeRay(i,j);
		  Vector3 colour = Trace(ray, 0);

		  // colour is within [0,1] boundaries, however it may have overflown so make the max 1
		  // colours multiplied by 255 to project into [0,255] colour
		  pixel[0]=(colour.x>1?1:colour.x)*255;
		  pixel[1]=(colour.y>1?1:colour.y)*255;
		  pixel[2]=(colour.z>1?1:colour.z)*255;

		  (void) fwrite(pixel, 1, 3, fp);
		}
	}
	(void) fclose(fp);
}

Vector3 Scene::Trace(Ray ray, int depth) {
	// Ray-Trace; retrieve colour for given ray


	// Retrieve the closest object which intersects with our Ray
	SceneObject *object=NULL;
	Vector3 pHit, nHit; // point of intersection on the object, and its normal
	float lastHit = INFINITY, t;
	Vector3 raydir=ray.dir;
	for (int i=0; i<scene_objects.size(); i++) {
		Vector3 pHiti, nHiti; // hit-points for this object
		if (ray.intersect(scene_objects[i], pHiti, nHiti, t)) {
			if (t<lastHit) {
				// this object is closer than previous object
				pHit=pHiti;
				nHit=nHiti;
				object=scene_objects[i];
				lastHit=t;
			}
		}
	}
	if (!object) return background;  // background instead


	// fix normal if necessary
	if (ray.dir.dot(nHit)>0) nHit*=-1;
	nHit.normalize();
	
	/*
	 * Colour Retrieval
	 **/
	Vector3 colour;
	Vector3 normOffset=nHit*0.02; // offset slightly towards the normal

	if (depth < max_rays && (object->reflective || object->transparent)) {
		// Reflection/Refraction calculations


		/* Fresnel Effect
		 *
		 * 	Fresnel is accomplished by taking the cos(angle) at which the ray hits
		 *	the point's normal of the given object; and creating a specular
		 *	characteristic out of that point.
		 *
		 *	R_f ~= spec + (1-spec)(1-cos(angle))^5
		 **********/
		float rayHitAngle = ray.dir.dot(nHit);
		float spec=0.2; // specular colour (determines material type)
		float fresnel = spec + (1-spec)*pow(1+(rayHitAngle>0?0:rayHitAngle),5);


		// Reflection
		Ray reflectionRay(
				(pHit + normOffset),
				(ray.dir - nHit*2*rayHitAngle));
		Vector3 reflection = Trace(reflectionRay, depth+1);
		reflection *= fresnel;


		// Refraction
		Vector3 refraction = Vector3(0,0,0);
		if (object->transparent) {
			float tilt = 1/1.1;
			float transparency=0.5;
			Ray refrray(
					(pHit - normOffset),
					(ray.dir * tilt - nHit*(tilt*rayHitAngle + sqrt(1-tilt*tilt*(1-rayHitAngle*rayHitAngle)))));
			refraction = Trace(refrray, depth+1);
			refraction*=transparency*(1-fresnel);
		}

		
		// Calculate the colour for this raycast
		colour = (reflection + refraction);
		colour.x*=object->col.x;
		colour.y*=object->col.y;
		colour.z*=object->col.z;
	} else {
		// No reflection to be done; simple Diffuse calculation

		// Find our lights and calculate a diffuse/shadow for each light
		for (int i=0; i<scene_objects.size(); i++) {
			if (scene_objects[i]->whatami()=="Light") {

				Vector3 lightDir = scene_objects[i]->pos - pHit;
				lightDir.normalize();
				float nDotL = nHit.dot(lightDir);
				if (nDotL<0) nDotL=0;

				// Shadow Calculation
				// Determine if there is an object between the light and hitpoint
				bool shadow=false;
				Ray lightRay(pHit + normOffset, lightDir);
				for (int j=0; j<scene_objects.size(); j++) {
					if (i!=j) {
						Vector3 lPoint, lNorm; float t0;
						if (lightRay.intersect(scene_objects[j], lPoint, lNorm, t0)) {
							shadow=true;
							break;
						}
					}
				}
				if (shadow) continue; // shadow is pure black, and does not need to be added to colour


				// Calculate simple Diffuse
				SceneLight* light=(SceneLight*)scene_objects[i];
				colour += Vector3(
						object->col.x * scene_objects[i]->light.x,
						object->col.y * scene_objects[i]->light.y,
						object->col.z * scene_objects[i]->light.z) * nDotL;
			}
		}
	}

	return colour + object->light;
}

