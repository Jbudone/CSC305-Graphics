/*
 * CSc 305: Assignment 4
 * Simple Ray-Tracer
 *
 * a basic ray-tracer; loading a scenefile with a floor (plane) and
 * spheres to raytrace and generate a .png image. The program takes
 * an argument -R to accept any number of rays to be casted from
 * each pixel.
 **/

#include <string>
#include <cstdio>
#include <cstdlib>


#include "scene.h"

using namespace std;

// Starting Position
// args -S [scenefile]
// 		-R [num_rays]
// int main(int argc, char **argv) {
int main(int argc, char **argv) {

	// Default Args
	int num_rays=3;
	string scenefile="scenes/default.scene";

	// Load Arguments
	// note: argv[0]=='./build_name'
	printf("%s usage:  %s [-R num_rays] [-S scenefile.scene]\n",argv[0],argv[0]);
	if (argc>2) {
		int argc_R=0, argc_S=0; // which args are which
		if (string(argv[1])=="-R") argc_R=1;
		else if (argc>3 && string(argv[3])=="-R") argc_R=3;

		if (string(argv[1])=="-S") argc_S=1;
		else if (argc>3 && string(argv[3])=="-S") argc_S=3;

		if (argc_R) {
			num_rays=atoi(argv[argc_R+1]);
			printf("Found -R number of rays: %i\n",num_rays);
		} else {
			printf("No -R found, defaulting to number of rays: %i\n",num_rays);
		}
		if (argc_S) {
			scenefile=string(argv[argc_S+1]);
			printf("Found -S scenefile: %s\n",scenefile.c_str());
		} else {
			printf("No -S found, defaulting to scenefile: %s\n",scenefile.c_str());
		}
	} else {
		printf("defaulting to num_rays=%i and scenefile=%s\n",num_rays,scenefile.c_str());
	}
	

	// Load Scenefile
	try {
		Scene scene(scenefile);
		scene.raytrace(num_rays);
	} catch (exception& e) {
		printf("Could not render scene. Aborting\n");
	}
	
	return -1;
}


