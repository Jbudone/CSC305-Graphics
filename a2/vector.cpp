#include "vector.h"

Vector3::Vector3(float m_x/* = 0.0f*/, float m_y/* = 0.0f*/, float m_z/* = 0.0f*/)
    : x(m_x),
      y(m_y),
      z(m_z)
{
}

Vector4::Vector4(float m_x/* = 0.0f*/, float m_y/* = 0.0f*/, float m_z/* = 0.0f*/, float m_w/* = 1.0f*/)
    : x(m_x),
      y(m_y),
      z(m_z),
      w(m_w)
{

}


/***********************************************************************************************/
/** Vector 3 stuff **/

// Assignment/Copy/Conversion operations
Vector3& Vector3::operator= (Vector3 const &vec) { x=vec.x; y=vec.y; z=vec.z; return *this; }
Vector3::Vector3(Vector3 const &vec) { x=vec.x; y=vec.y; z=vec.z; }
Vector3::operator Vector4() const { return Vector4(x,y,z,1); } //w=1.0 since that is constructor default

// Basic Operations
Vector3 Vector3::operator+ (Vector3 const &vec) { return Vector3(x+vec.x, y+vec.y, z+vec.z); }
Vector3 Vector3::operator- (Vector3 const &vec) { return Vector3(x-vec.x, y-vec.y, z-vec.z); }
Vector3 Vector3::operator* (float scale) { return Vector3(scale*x, scale*y, scale*z); }

Vector3& Vector3::operator+= (Vector3 const &vec) { *this = ((*this) + vec); return *this; }
Vector3& Vector3::operator-= (Vector3 const &vec) { *this = ((*this) - vec); return *this; }
Vector3& Vector3::operator*= (float scale) { *this = ((*this) * scale); return *this; }

// Vector Algebra
float Vector3::dot(Vector3 const &vec) { return (x*vec.x + y*vec.y + z*vec.z); }
float Vector3::sqlength() { return dot(*this); }
Vector3 Vector3::cross(Vector3 const &vec) { return Vector3((y*vec.z)-(z*vec.y),(z*vec.x)-(x*vec.z),(x*vec.y)-(y*vec.x)); }
void Vector3::normalize() {
	float length=sqlength(); length = sqrt(length);
	if (length==0) return;
	x/=length; y/=length; z/=length;
}

void Vector3::print() { printf("vector3(%f,%f,%f)\n",x,y,z); }





/***********************************************************************************************/
/** Vector 4 stuff **/

// Assignment/Copy/Conversion operations
Vector4& Vector4::operator= (Vector4 const &vec) { x=vec.x; y=vec.y; z=vec.z; w=vec.w; return *this; }
Vector4::Vector4(Vector4 const &vec) { x=vec.x; y=vec.y; z=vec.z; w=vec.w; }
Vector4::operator Vector3() const { return Vector3(x,y,z); }

// Basic Operations
Vector4 Vector4::operator+ (Vector4 const &vec) { return Vector4(x+vec.x, y+vec.y, z+vec.z, w+vec.w); }
Vector4 Vector4::operator- (Vector4 const &vec) { return Vector4(x-vec.x, y-vec.y, z-vec.z, w-vec.w); }
Vector4 Vector4::operator* (float scale) { return Vector4(scale*x, scale*y, scale*z, scale*w); }

Vector4& Vector4::operator+= (Vector4 const &vec) { *this = ((*this) + vec); return *this; }
Vector4& Vector4::operator-= (Vector4 const &vec) { *this = ((*this) - vec); return *this; }
Vector4& Vector4::operator*= (float scale) { *this = ((*this) * scale); return *this; }

// Vector Algebra
float Vector4::dot(Vector4 const &vec) { return (x*vec.x + y*vec.y + z*vec.z + w*vec.w); }
float Vector4::sqlength() { return dot(*this); }
void Vector4::normalize() {
	float length=sqlength(); length = sqrt(length);
	if (length==0) return;
	x/=length; y/=length; z/=length; w/=length;
}
