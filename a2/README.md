
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
note: both camera modes use different settings, and reset upon switch

Arcball
Rotates the gaze vector accordingly (gaze=eye-target), then changes the eye position
based off the difference of the gaze vector (how much has the gaze vector rotated/moved)
The up vector simply takes the new gaze vector and rotates it 90deg along the local-X
space to make it perpendicular, and hence facing the upwards direction that we want.

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

* Arcball: Cannot rotate along both X and Y; only one or the other 
* Worldcrawler: Cannot rotate along X axis

