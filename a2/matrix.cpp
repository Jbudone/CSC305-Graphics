#include "matrix.h"

Matrix3x3::Matrix3x3()
{
    this->loadIdentity();
}

void Matrix3x3::loadIdentity()
{
    elements[0] = elements[4] = elements[8] = 1;
    elements[1] = elements[2] = elements[3] = elements[5] = elements[6] = elements[7] = 0;
}

Matrix4x4::Matrix4x4()
{
    loadIdentity();
}

void Matrix4x4::loadIdentity()
{
    elements[0] = elements[5] = elements[10] = elements[15] = 1;
    elements[1] = elements[2] = elements[3] = elements[4] = elements[6] = elements[7]
    = elements[8] = elements[9] = elements[11] = elements[12] = elements[13] = elements[14] = 0;
}

/********************************************************************************************/
/** Projections and View Matrices **/

Matrix4x4& Matrix4x4::projectPerspective(float fov,float aspect,float near,float far) {
	Matrix4x4 mat;
	*this = (mat); // clear elements
	float top = near * tan(fov * 0.5f);
	float bottom = -top;
	float left = bottom * aspect;
	float right = top * aspect;
	elements[0] = near / right;
	elements[5] = near / top;
	elements[10] = (-far - near) / (far - near);
	elements[11] = -1;
	elements[14] = (-2 * far * near) / (far - near);
	elements[15] = 0;
	return *this;
}

Matrix4x4& Matrix4x4::projectOrthographic(float left,float right,float top,float bottom,float near,float far) {
	Matrix4x4 mat;
	*this = (mat); // clear elements
	elements[0]=2/(right-left);
	elements[5]=2/(top-bottom);
	elements[10]=-2/(far-near);
	elements[12]=-(right+left)/(right-left);
	elements[13]=-(top+bottom)/(top-bottom);
	elements[14]=-(far+near)/(far-near);
	elements[15]=1;
	return *this;
}


Matrix4x4& Matrix4x4::createView(Vector3 eye,Vector3 at,Vector3 up) {
	Vector3 a;
	a=(eye-at); a.normalize();
	Vector3 zaxis = a;
	a=up; a=a.cross(zaxis); a.normalize();
	Vector3 xaxis = a;
	a=zaxis; a=a.cross(xaxis); a.normalize();
	Vector3 yaxis = a;

	Matrix4x4 orientation;
	orientation[0]=xaxis.x; orientation[1]=xaxis.y; orientation[2]=xaxis.z;
	orientation[4]=yaxis.x; orientation[5]=yaxis.y; orientation[6]=yaxis.z;
	orientation[8]=zaxis.x; orientation[9]=zaxis.y; orientation[10]=zaxis.z;
	// orientation[0]=xaxis.x; orientation[1]=xaxis.y; orientation[2]=xaxis.z;
	// orientation[4]=yaxis.x; orientation[5]=yaxis.y; orientation[6]=yaxis.z;
	// orientation[8]=zaxis.x; orientation[9]=zaxis.y; orientation[10]=zaxis.z;
	orientation[12]=-(xaxis.dot(eye));
	orientation[13]=-(yaxis.dot(eye));
	orientation[14]=-(zaxis.dot(eye));
	orientation[15]=1;
	*this = orientation;
	return *this;
}

// source: http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
Matrix4x4& Matrix4x4::invert() {
	float inv[16], det;

    inv[0] = elements[5]  * elements[10] * elements[15] - 
             elements[5]  * elements[11] * elements[14] - 
             elements[9]  * elements[6]  * elements[15] + 
             elements[9]  * elements[7]  * elements[14] +
             elements[13] * elements[6]  * elements[11] - 
             elements[13] * elements[7]  * elements[10];

    inv[4] = -elements[4]  * elements[10] * elements[15] + 
              elements[4]  * elements[11] * elements[14] + 
              elements[8]  * elements[6]  * elements[15] - 
              elements[8]  * elements[7]  * elements[14] - 
              elements[12] * elements[6]  * elements[11] + 
              elements[12] * elements[7]  * elements[10];

    inv[8] = elements[4]  * elements[9] * elements[15] - 
             elements[4]  * elements[11] * elements[13] - 
             elements[8]  * elements[5] * elements[15] + 
             elements[8]  * elements[7] * elements[13] + 
             elements[12] * elements[5] * elements[11] - 
             elements[12] * elements[7] * elements[9];

    inv[12] = -elements[4]  * elements[9] * elements[14] + 
               elements[4]  * elements[10] * elements[13] +
               elements[8]  * elements[5] * elements[14] - 
               elements[8]  * elements[6] * elements[13] - 
               elements[12] * elements[5] * elements[10] + 
               elements[12] * elements[6] * elements[9];

    inv[1] = -elements[1]  * elements[10] * elements[15] + 
              elements[1]  * elements[11] * elements[14] + 
              elements[9]  * elements[2] * elements[15] - 
              elements[9]  * elements[3] * elements[14] - 
              elements[13] * elements[2] * elements[11] + 
              elements[13] * elements[3] * elements[10];

    inv[5] = elements[0]  * elements[10] * elements[15] - 
             elements[0]  * elements[11] * elements[14] - 
             elements[8]  * elements[2] * elements[15] + 
             elements[8]  * elements[3] * elements[14] + 
             elements[12] * elements[2] * elements[11] - 
             elements[12] * elements[3] * elements[10];

    inv[9] = -elements[0]  * elements[9] * elements[15] + 
              elements[0]  * elements[11] * elements[13] + 
              elements[8]  * elements[1] * elements[15] - 
              elements[8]  * elements[3] * elements[13] - 
              elements[12] * elements[1] * elements[11] + 
              elements[12] * elements[3] * elements[9];

    inv[13] = elements[0]  * elements[9] * elements[14] - 
              elements[0]  * elements[10] * elements[13] - 
              elements[8]  * elements[1] * elements[14] + 
              elements[8]  * elements[2] * elements[13] + 
              elements[12] * elements[1] * elements[10] - 
              elements[12] * elements[2] * elements[9];

    inv[2] = elements[1]  * elements[6] * elements[15] - 
             elements[1]  * elements[7] * elements[14] - 
             elements[5]  * elements[2] * elements[15] + 
             elements[5]  * elements[3] * elements[14] + 
             elements[13] * elements[2] * elements[7] - 
             elements[13] * elements[3] * elements[6];

    inv[6] = -elements[0]  * elements[6] * elements[15] + 
              elements[0]  * elements[7] * elements[14] + 
              elements[4]  * elements[2] * elements[15] - 
              elements[4]  * elements[3] * elements[14] - 
              elements[12] * elements[2] * elements[7] + 
              elements[12] * elements[3] * elements[6];

    inv[10] = elements[0]  * elements[5] * elements[15] - 
              elements[0]  * elements[7] * elements[13] - 
              elements[4]  * elements[1] * elements[15] + 
              elements[4]  * elements[3] * elements[13] + 
              elements[12] * elements[1] * elements[7] - 
              elements[12] * elements[3] * elements[5];

    inv[14] = -elements[0]  * elements[5] * elements[14] + 
               elements[0]  * elements[6] * elements[13] + 
               elements[4]  * elements[1] * elements[14] - 
               elements[4]  * elements[2] * elements[13] - 
               elements[12] * elements[1] * elements[6] + 
               elements[12] * elements[2] * elements[5];

    inv[3] = -elements[1] * elements[6] * elements[11] + 
              elements[1] * elements[7] * elements[10] + 
              elements[5] * elements[2] * elements[11] - 
              elements[5] * elements[3] * elements[10] - 
              elements[9] * elements[2] * elements[7] + 
              elements[9] * elements[3] * elements[6];

    inv[7] = elements[0] * elements[6] * elements[11] - 
             elements[0] * elements[7] * elements[10] - 
             elements[4] * elements[2] * elements[11] + 
             elements[4] * elements[3] * elements[10] + 
             elements[8] * elements[2] * elements[7] - 
             elements[8] * elements[3] * elements[6];

    inv[11] = -elements[0] * elements[5] * elements[11] + 
               elements[0] * elements[7] * elements[9] + 
               elements[4] * elements[1] * elements[11] - 
               elements[4] * elements[3] * elements[9] - 
               elements[8] * elements[1] * elements[7] + 
               elements[8] * elements[3] * elements[5];

    inv[15] = elements[0] * elements[5] * elements[10] - 
              elements[0] * elements[6] * elements[9] - 
              elements[4] * elements[1] * elements[10] + 
              elements[4] * elements[2] * elements[9] + 
              elements[8] * elements[1] * elements[6] - 
              elements[8] * elements[2] * elements[5];

    det = elements[0] * inv[0] + elements[1] * inv[4] + elements[2] * inv[8] + elements[3] * inv[12];

    if (det == 0)
        return *this;

    det = 1.0 / det;

    for (int i = 0; i < 16; i++)
        elements[i] = inv[i] * det;

	return *this;
}

/********************************************************************************************/
/** Matrix Algebra **/


/** These methods are the the core functionality of our linear algebra
 * 	every other method uses these methods in order to calculate their results
 **/

Matrix4x4 Matrix4x4::operator+(Matrix4x4 const &mat) {
	for (int i=0; i<=15; i++) {
		elements[i]+=mat[i];
	}
	
	return *this;
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 const &mat) {
	Matrix4x4 _mat;
	for (int i=0, row=0, col=0, j; i<=15; i++) {
		row=i%4;
		col=i/4;
		_mat[i]=0; // clear this element
		for (j=0; j<4; j++) { // beautiful formula O(n) time
			_mat[i]+=(elements[row+(4*j)]*mat[(4*col)+j]);
		}
	}
	
	return _mat;
}

Matrix4x4 Matrix4x4::operator*(float factor) {
	for (int i=0; i<=15; i++) {
		elements[i]*=factor;
	}

	return *this;
}

Vector3 Matrix3x3::operator*(Vector3 const &vec) {
	Vector3 _vec;
	_vec.x=(elements[0]*vec.x + elements[3]*vec.y + elements[6]*vec.z);
	_vec.y=(elements[1]*vec.x + elements[4]*vec.y + elements[7]*vec.z);
	_vec.z=(elements[2]*vec.x + elements[5]*vec.y + elements[8]*vec.z);
	return _vec;
}

/**************************************/

/** Geometry Operations
 * convenience operations for geometries
 **/

Matrix3x3& Matrix3x3::scale(float x=1, float y=1, float z=1) {
	elements[0]*=x;
	elements[4]*=y;
	elements[8]*=z;
	return *this;
}

Matrix4x4& Matrix4x4::scale(float x=1, float y=1, float z=1, float w=1) {
	elements[0]*=x;
	elements[5]*=y;
	elements[10]*=z;
	elements[15]*=w;
	return *this;
}

Matrix3x3& Matrix3x3::translate(float x=0, float y=0, float z=0) {
	elements[6]+=x;
	elements[7]+=y;
	elements[8]+=z;
	return *this;
}

Matrix4x4& Matrix4x4::translate(float x=0, float y=0, float z=0, float w=0) {
	elements[12]+=x;
	elements[13]+=y;
	elements[14]+=z;
	elements[15]+=w;
	return *this;
}

Matrix4x4& Matrix4x4::rotateX(float r) {
	Matrix4x4 rot;
	rot[5]=cos(r);
	rot[10]=cos(r);
	rot[9]=-sin(r);
	rot[6]=sin(r);
	*this = (*this)*rot;
	return *this;
}

Matrix4x4& Matrix4x4::rotateY(float r) {
	Matrix4x4 rot;
	rot[0]=cos(r);
	rot[10]=cos(r);
	rot[2]=-sin(r);
	rot[8]=sin(r);
	*this = (*this)*rot;
	return *this;
}

Matrix4x4& Matrix4x4::rotateZ(float r) {
	Matrix4x4 rot;
	rot[0]=cos(r);
	rot[5]=cos(r);
	rot[4]=-sin(r);
	rot[1]=sin(r);
	*this = (*this)*rot;
	return *this;
}

Matrix3x3& Matrix3x3::rotateX(float r) {
	*this = ((Matrix4x4)*this).rotateX(r);
	return *this;
}

Matrix3x3& Matrix3x3::rotateY(float r) {
	*this = ((Matrix4x4)*this).rotateY(r);
	return *this;
}

Matrix3x3& Matrix3x3::rotateZ(float r) {
	*this = ((Matrix4x4)*this).rotateZ(r);
	return *this;
}

/**************************************/

/** Printing matrices to console
 *  pretty useful for debugging purposes..
 **/

void Matrix3x3::print() {
	printf("| %f %f %f |\n", elements[0], elements[3], elements[6]);
	printf("| %f %f %f |\n", elements[1], elements[4], elements[7]);
	printf("| %f %f %f |\n", elements[2], elements[5], elements[8]);
	printf("\n");
	printf("\n");
}

void Matrix4x4::print() {
	printf("| %f %f %f %f |\n", elements[0], elements[4], elements[8], elements[12]);
	printf("| %f %f %f %f |\n", elements[1], elements[5], elements[9], elements[13]);
	printf("| %f %f %f %f |\n", elements[2], elements[6], elements[10], elements[14]);
	printf("| %f %f %f %f |\n", elements[3], elements[7], elements[11], elements[15]);
	printf("\n");
	printf("\n");
}


/**************************************/

/** Array type subscripts
 * Note we have to take care of the two cases,
 *    this[0] = that[0];
 *   
 *   this[0] (float&) is being changed (hence a ref val)
 *   that[0] (float)  is constant (hence a const val - necessary when that is a constant)
 **/

float& Matrix3x3::operator[] (int i) {
	return elements[i];
}

float Matrix3x3::operator[] (int i) const {
	return elements[i];
}

float& Matrix4x4::operator[] (int i) {
	return elements[i];
}

float Matrix4x4::operator[] (int i) const {
	return elements[i];
}



/**************************************/

/** Conversions
 * Matrix3x3 to Matrix4x4 and back again
 **/

Matrix3x3::operator Matrix4x4() const {
	Matrix4x4 mat;

	mat[0]=elements[0];
	mat[1]=elements[1];
	mat[2]=elements[2];
	mat[3]=0;

	mat[4]=elements[3];
	mat[5]=elements[4];
	mat[6]=elements[5];
	mat[7]=0;

	mat[8]=elements[6];
	mat[9]=elements[7];
	mat[10]=elements[8];
	mat[11]=0;

	mat[12]=0;
	mat[13]=0;
	mat[14]=0;
	mat[15]=1;

	return mat;
}

Matrix4x4::operator Matrix3x3() const {
	Matrix3x3 mat;

	mat[0]=elements[0];
	mat[1]=elements[1];
	mat[2]=elements[2];
	
	mat[3]=elements[4];
	mat[4]=elements[5];
	mat[5]=elements[6];

	mat[6]=elements[8];
	mat[7]=elements[9];
	mat[8]=elements[10];

	return mat;
}



/**************************************/

/** Assignment/Copy operations
 **/

Matrix3x3::Matrix3x3(Matrix3x3 const &mat) {
	for (int i=0; i<=8; i++) {
		elements[i]=mat[i];
	}
}

Matrix4x4::Matrix4x4(Matrix4x4 const &mat) {
	for (int i=0; i<=15; i++) {
		elements[i]=mat[i];
	}
}

Matrix3x3& Matrix3x3::operator=(Matrix3x3 const &mat) {
	for (int i=0; i<=8; i++) {
		elements[i]=mat[i];
	}

	return *this;
}

Matrix4x4& Matrix4x4::operator=(Matrix4x4 const &mat) {
	for (int i=0; i<=15; i++) {
		elements[i]=mat[i];
	}

	return *this;
}



/**************************************/

/** Basic operations (add, subtract, multiply, scale)
 **/

Matrix3x3 Matrix3x3::operator+(Matrix3x3 const &mat) {
	return ((( Matrix4x4 ) *this) + (( Matrix4x4 ) mat));
}

Matrix3x3 Matrix3x3::operator-(Matrix3x3 const &mat) {
	return ((( Matrix4x4 ) *this) - (( Matrix4x4 ) mat));
}


Matrix3x3 Matrix3x3::operator*(Matrix3x3 const &mat) {
	return ((( Matrix4x4 ) *this) * (( Matrix4x4 ) mat));
}

Matrix3x3 Matrix3x3::operator*(float factor) {
	return ((( Matrix4x4 ) *this) * factor);
}

Matrix3x3& Matrix3x3::operator+=(Matrix3x3 const &mat) {
	*this = ((*this) + (mat));
	return *this;
}

Matrix3x3& Matrix3x3::operator-=(Matrix3x3 const &mat) {
	*this = ((*this) - (mat));
	return *this;
}

Matrix3x3& Matrix3x3::operator*=(const Matrix3x3 &mat) {
	*this = ((*this) * (mat));
	return *this;
}

Matrix3x3& Matrix3x3::operator*=(float factor) {
	*this = ((*this) * factor);
	return *this;
}

Matrix4x4 Matrix4x4::operator-(Matrix4x4 const &mat) {
	return ((*this) + (((Matrix4x4)mat)*-1));
}

Matrix4x4& Matrix4x4::operator+=(Matrix4x4 const &mat) {
	*this = ((*this) + (mat));
	return *this;
}

Matrix4x4& Matrix4x4::operator-=(Matrix4x4 const &mat) {
	*this = ((*this) - (mat));
	return *this;
}

Matrix4x4& Matrix4x4::operator*=(Matrix4x4 const &mat) {
	*this = ((*this) * (mat));
	return *this;
}

Matrix4x4& Matrix4x4::operator*=(float factor) {
	*this = ((*this) * factor);
	return *this;
}

