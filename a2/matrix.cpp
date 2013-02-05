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
	return ((*this * -1) + mat);
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

