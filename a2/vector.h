#ifndef VECTOR_H
#define VECTOR_H

#include <cmath> // necessary for square roots
#include <cstdio>
/**
 *  @todo assignment two
 *  extend these classes to support the basic linear algebra functions, including dot and cross product
 */

/**
 * @brief The Vector3 class
 * represents a 3 dimensional vector.
 * given a Vector3 myVec3; the single elements can either
 * be accessed using myVec3.x myVec3.y myVec3.z or myVec3.elements[index]
 */
class Vector4; // Necessary for conversions
class Vector3
{
public:

    /**
     * we use a union, so the three values x,y,z and elements[3] occupy the
     * same region in memory, this we can use both of them for reading and
     * writing to the elements.
     */
    union
    {
        struct
        {
            float x, y, z;
        };
        float elements[3];
    };

    /**
     * @brief Vector3 constructor
     * @param m_x the x value
     * @param m_y the y value
     * @param m_z the z value
     */
    Vector3(float m_x = 0.0f, float m_y = 0.0f, float m_z = 0.0f);


	/******************************************************************************/
	/** Vector Algebra **/
	Vector3& operator= (Vector3 const&);
	Vector3(Vector3 const&);
	operator Vector4() const;
	Vector3 operator+ (Vector3 const&);
	Vector3 operator- (Vector3 const&);
	Vector3 operator* (float);
	Vector3& operator+= (Vector3 const&);
	Vector3& operator-= (Vector3 const&);
	Vector3& operator*= (float);

	float dot(Vector3 const&);
	Vector3 cross(Vector3 const&);
	float sqlength();
	void normalize();
	void print();
};

/**
 * @brief The Vector4 class
 * represents a 4 dimensional vector.
 * given a Vector4 myVec4; the single elements can either
 * be accessed using myVec4.x myVec4.y myVec4.z myVec4.w or myVec4.elements[index]
 */
class Vector4
{
public:

    /**
     * we use a union, so the four values x,y,z,w and elements[4] occupy the
     * same region in memory, this we can use both of them for reading and
     * writing to the elements.
     */
    union
    {
        struct
        {
            float x, y, z, w;
        };
        float elements[4];
    };

    /**
     * @brief Vector4
     * @param m_x the x value
     * @param m_y the y value
     * @param m_z the z value
     * @param m_w the w value
     */
    Vector4(float m_x = 0.0f, float m_y = 0.0f, float m_z = 0.0f, float m_w = 1.0f);


	/******************************************************************************/
	/** Vector Algebra **/
	Vector4& operator= (Vector4 const&);
	Vector4(Vector4 const&);
	operator Vector3() const;
	Vector4 operator+ (Vector4 const&);
	Vector4 operator- (Vector4 const&);
	Vector4 operator* (float);
	Vector4& operator+= (Vector4 const&);
	Vector4& operator-= (Vector4 const&);
	Vector4& operator*= (float);

	float dot(Vector4 const&);
	float sqlength();
	void normalize();
};

#endif // VECTOR_H
