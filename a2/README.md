
# Assignment 2


Matrices and Vectors
====================

Basic operations for matrices and vectors have been included in the given
classes (Matrix3x3, Matrix4x4, Vector3, Vector4). All of which implement operator
overloading for cleanliness and efficiency (along with bonus marks, naturally).
Matrices have been written in such a way to maximize efficiency, where all of the
complexity was given to the Matrix4x4 +,* routines; every other operation uses
those routines, even the Matrix3x3 operations which convert into Matrix4x4's 
first, run those routines, and then get converted back.

Model Matrix
=============

The model matrix is built via, mModelMatrix=(translation*rotation*scale) when 
mUsePostMultiply is true;      mModelMatrix=(scale*rotation*translation) when
mUsePostMultiply is false. These both result in very different effects during
geometry manipulations.

Projection Matrices
================
note: settings stored in basicopenview.cpp (initializeGL method)
note: takes care of window-resize events

Orthographic Matrix
projects vertices to the view plane, anything within the boundary settings given in
basicopenview.cpp; basically vertices are interpolated into [-1,1] range, with the
z-component ignored

Projection Matrix
projects vertices in a way similar to the way we perceive real-life objects

View Matrix
our camera view projection; rotation (where are we facing), translation (where are
we in space). This is handled mostly within the camera movement.

Camera Movement
===============

Arcball
Picture a sphere centered at the origin, and a plane tangent to some point on that
sphere, then our camera is aligned to and placed on that plane, looking at the
origin. Moving around simply translates the camera to the origin, rotates the camera
as expected, then appends the inverse translation of what we applied to get to the 
origin.

World Crawler
Treats the camera as a FPS type camera. Move around using either WASD or Up/Left/Down
/Right, and the mouse to look around (rotate along the local X or Y axis). The 
movement simply waits for a keydown event to trigger, then adds 1 to the movement 
vector; when that key is released in keyup it subtracts 1 from that component of the 
movement vector. A QTimer is initialized in mainwindow.cpp and calls update_timer 
every 100ms, which takes a scaled version of the movement vector and adds it to the
translation portion of the view matrix (hence moving the camera).

TODO/Errors
=============

* Adding a new geometry after already having scaled/translated geometries will NOT
	give the new geometry its intended initial manipulations (outside of my range)

