
Assignment 4
--------------

CSc 305 A01
name: Joshua Braendel
student id: V00482121
Mar 25. 2013

Raytrace Contest: use screenshot2.png


A simple raytracer which calculates reflections, refractions (transparency), diffuse, and shadows.
The idea is that a ray is cast out of every pixel into the world, intersected with an object, and
further raycasted through reflections and refractions; then returned as a colour for the given 
pixel, and printed into an .ppm image


Marking Criteria
======

✓ 1 pt for code comments & README.txt file
✓ 1 pt for writing an image to disc
✓ 1 pt for generating the rays through each pixel and intersecting with a plane as floor
✓ 1 pt for intersecting rays with a sphere
✓ 1 pt for calculating the diffuse and specular color
✓ 1 pt for calculating if a surface point is in the shadow or not
✓ 1 pt for calculating reflections with arbitrary recursion depth
✓ 1 pt for shooting an arbitrary number of rays per pixel
✓ 2 pt for combining Phong illumination with shadowing and reflections

# Bonus
✓ 2 pt for adding refractions

Running
======

# compiling
'''linux''' `make`
'''mac''' `xcodebuild`

# running
./main [-R (number of rays)] [-S (scene file)]

-R: the maximum depth of rays to be casted
-S: the scenefile (already made scenefiles stored within scene/ )


Scenes
======

Scenes are contained in files with the following format,
All numbers are loaded as floats (1 loads as 1.0f)

<position>	represents:  [x pos] [y pos] [z pos]
<colour>	represents:  [r col] [g col] [b col]
<radius>	represents:  [radius]
<intensity> represents:  [intensity]
<material>  represents:  [R|T]
		R  for reflective
		T  for transparent (refractive)
		none for plain


# Comments start with a #-tag
scene <width> <height> <fov> <background-colour>
light <position> <colour> <intensity>
floor <position> <colour>
sphere <position> <colour> <radius> <material>


Colour Calculations
======

Basic concept is that a ray is cast out from any given pixel, and projected into the worldspace of
the scene. This ray is checked against every object to find if any intersect with it, and if so
which is the closest intersecting object. That object is then put through a few calculations to
determine the result of the colour:

# Reflective
	if the object is reflective, create a ray from the reflection angle to the hitpoint, and cast
	it into another raytrace to retrieve that colour; the resulting reflection colour is multiplied
	by the fresnel effect equation

# Refraction
	if the object is transparent, create a ray from the refraction angle to the hitpoint, and cast
	it into another raytrace to retrieve that colour; the resulting refraction colour is multiplied
	by a level of transparency and the inverse of the fresnel effect equation

# Diffse
	if there the rays are cast too deep, or the object is neither reflective nor refractive, then
	calculate a simple diffuse colour. For each light within the scene, add its diffuse colour
	to the resulting colour. Before calculating the individual diffuse colour, check if there are 
	any objects between the hitpoint and the light, and if so make the diffuse colour a shadow;
	otherwise use a simple diffuse (lightcolour * objectcolour * cos(hit-angle))


Intersections
======

````
 Plane intersection explained
 Assume the the plane is short and runs forever (x-inf, z-inf, y=1)
 pHit: o+td; only hits where o_y + td_y = y
````

````
 Sphere intersection explained
 Sphere: x^2 + y^2 + z^2 = r^2
 	if ray intersects sphere then this equation holds
 	let O = (ray_pos - obj_center)
	(O_x+td_x)^2 + (O_y+td_y)^2 + (O_z+td_z)^2 = r^2
	[(O_x*O_x) + 2td_xO_x + t^2(d_x*d_x)] + [(O_y*O_y) + 2td_yO_y + t^2(d_y*d_y)] + [(O_z*O_z) + 2td_zO_z + t^2(d_z*d_z)] = r^2
	[(O_x*O_x) + (O_y*O_y) + (O_z*O_z)] + 2t[d_xO_x + d_yO_y + d_zO_z] + t^2[(d_x*d_x) + (d_y*d_y) + (d_z*d_z)] = r^2
	|O| + 2t|dO| + t^2|d| = r^2
	t^2|d| + 2t|dO| + (|O|-r^2) = 0
	t^2 + 2t|dO| + (|O|-r^2) = 0   ; |d| direction vector is normalized

	Given that equation, we can solve for t with the quadratic equation
	a=1, b=2|dO|, c=(|O|-r^2)
	t = (-b +- sqrt(b^2 - 4ac))/2a
	t = (-b +- sqrt(b^2 - ac))/a   ; let b=d (divide out the 2)
	t = (-dO +- sqrt(dO - (O-r^2)))

	let o = ray position, c = object center (expanding O)
	t = (-d(o-c)(o-c) +- sqrt(d(o-c)(o-c) - (o-c)(o-c) + r^2))

	therefore the hit points are,
	t = -d(o-c) + sqrt(dd(o-c)(o-c) - (o-c)(o-c)+r^2)
	t = -d(o-c) - sqrt(dd(o-c)(o-c) - (o-c)(o-c)+r^2)

  these hits will NOT exist if the results are imaginary
  ray MISSES when  
   *  d(o-c) < 0
   *  (o-c)(o-c) - d(o-c)*d(o-c) > r^2
````

TODO
======

 * soft shadows w/ multiple lights

