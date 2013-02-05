
Assignment 1
===============

Simple 2d opengl functionality using Qt
assignment includes rendering, translating and scaling geometries

Rendering
===============

For every geometry the normal, vertex, colour and texcoord are
rendered (if the parameter index is found for them). 

Mouse Input
===============

To convert to opengl coordinates [-1,1] we simply set X-min as
-1, and X-max as 1. Scale the mouse relative mouse coordinates
by 2, then divide by X-max, this takes us within a range of [0,2]
simply subtract 1 and we're within opengl coordinates [-1,1].

Translation
===============

Simply, every vertex in every geometry has the delta displacement
added to each of its attributes.

Scaling
===============

We are given a scale  0.1<s`<1.0, and a variable which holds the 
previous scale level s. 
Let x` be the new position for the attribute in a vertex (x, y, z),
Let x  be the current position
Let x0 be the initial position

initially,
	x` = x*s`

however, this will only work once. Otherwise scaling to 0.8, and then
to 0.5, will instead scale us to 0.8, and then 0.5 of 0.8 (which is 0.8*0.5=0.4)
	x` = x0*s`
	x0 = x`/s`
	therefore after the initial scale,
	x` = x0*s`
	x` = (x/s)*s`
	x` = x * (s`/s)
	x` *= s`/s

And our scale will always work, for any s`!=0

