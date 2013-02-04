#ifndef VECTOR_H
#define VECTOR_H

class Vector3
{
public:

    union
    {
        struct
        {
            float x, y, z;
        };
        float elements[3];
    };


    Vector3(float m_x = 0.0f, float m_y = 0.0f, float m_z = 0.0f);


};

class Vector4
{
public:

    union
    {
        struct
        {
            float x, y, z, w;
        };
        float elements[4];
    };

    Vector4(float m_x = 0.0f, float m_y = 0.0f, float m_z = 0.0f, float m_w = 1.0f);
};

#endif // VECTOR_H
