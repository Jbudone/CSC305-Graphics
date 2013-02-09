#ifndef MATRIX_H
#define MATRIX_H

#include <cstdio> // used for debugging purposes (printf)
#include <cmath>
#include "vector.h"
/**
 *  @todo assignment two
 *  1. extend these matrix classes to support all the basic linear algebra functions
 *  (add, subtract, multiply)
 *  2. add convenience functions to create scale & rotation matrices around the available axes,
 *  and a translation matrix
 *  3. add functions to create the projection matrix versions.
 *  for perspective projection, this function should take the field of view, image ratio, near plane and far plane distance
 *  for orthographic projection it should take the left, right, top, bottom, near plane and far plane values
 *  4. add functions to create the view matrix using eye position, at position and the up vector
 */

/**
 *	@class	Matrix3x3
 *	@brief	3 by 3 Matrix class
 *	Homogenous 3x3 Matrix, onedimensional array (like opengl), column major
 *	|0 3 6|
 *	|1 4 7|
 *	|2 5 8|
 */
class Matrix4x4; // reference for matrix3x3 conversions to matrix4x4
class Matrix3x3
{
public:

    float elements[9];/**< array storing the values of the matrix. */

    /**
     *	default constructor
     *	generates the identity matrix
     */
    Matrix3x3();

    /**
     *	generates the identity matrix
     */
    void loadIdentity();

	/*************************************************************************/
	/** Matrix Algebra **/
	void print();
	Matrix3x3& operator= (Matrix3x3 const&);
	Matrix3x3(Matrix3x3 const&);
	operator Matrix4x4() const;
	float& operator[] (int);
	float operator[] (int) const;
	Matrix3x3 operator+ (Matrix3x3 const&);
	Matrix3x3 operator- (Matrix3x3 const&);
	Matrix3x3 operator* (Matrix3x3 const&);
	Matrix3x3 operator* (float);
	Matrix3x3& operator+= (Matrix3x3 const&);
	Matrix3x3& operator-= (Matrix3x3 const&);
	Matrix3x3& operator*= (Matrix3x3 const&);
	Matrix3x3& operator*= (float);

	Matrix3x3& scale(float,float,float);
	Matrix3x3& translate(float,float,float);
	Matrix3x3& rotateX(float);
	Matrix3x3& rotateY(float);
	Matrix3x3& rotateZ(float);
};

/**
 *	@class	Matrix4x4
 *	@brief	4 by 4 matrix
 *	Homogenous 4x4 Matrix, onedimensional array (like opengl), column major
 *	|0 4 8  12|
 *	|1 5 9  13|
 *	|2 6 10 14|
 *	|3 7 11 15|
 */
class Matrix4x4
{
public:

    float elements[16];	/**< array storing the values of the matrix. */

    /**
     *	default constructor
     *	generates the identity matrix
     */
    Matrix4x4();

    /**
     *	generates the identity matrix
     */
    void loadIdentity();

	/*************************************************************************/
	/** Matrix Algebra **/
	void print();
	Matrix4x4& operator= (Matrix4x4 const&);
	Matrix4x4(Matrix4x4 const&);
	operator Matrix3x3() const;
	float& operator[] (int);
	float operator[] (int) const;
	Matrix4x4 operator+ (Matrix4x4 const&);
	Matrix4x4 operator- (Matrix4x4 const&);
	Matrix4x4 operator* (Matrix4x4 const&);
	Matrix4x4 operator* (float);
	Matrix4x4& operator+= (Matrix4x4 const&);
	Matrix4x4& operator-= (Matrix4x4 const&);
	Matrix4x4& operator*= (Matrix4x4 const&);
	Matrix4x4& operator*= (float);

	Matrix4x4& scale(float,float,float,float);
	Matrix4x4& translate(float,float,float,float);
	Matrix4x4& rotateX(float);
	Matrix4x4& rotateY(float);
	Matrix4x4& rotateZ(float);

	Matrix4x4& projectPerspective(float,float,float,float);
	Matrix4x4& projectOrthographic(float,float,float,float,float,float);
	Matrix4x4& createView(Vector3,Vector3,Vector3);
	Matrix4x4& invert();

};

#endif // MATRIX_H
