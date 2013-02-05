
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

