#ifndef VECTOR_H
#define VECTOR_H

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
};

#endif // VECTOR_H
