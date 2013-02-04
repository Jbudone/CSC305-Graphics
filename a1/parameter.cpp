#include "parameter.h"
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

template<>
void Parameter<int>::upload()
{
    if(mCPUData)
        glUniform1i(mHandle, * mCPUData);
}

template<>
void Parameter<float>::upload()
{
    if(mCPUData)
        glUniform1f(mHandle, * mCPUData);
}

template<>
void Parameter<Vector3>::upload()
{
    if(mCPUData)
        glUniform3fv(mHandle, 1, & (mCPUData->elements[0]));
}

template<>
void Parameter<Vector4>::upload()
{
    if(mCPUData)
        glUniform4fv(mHandle, 1, & (mCPUData->elements[0]));
}

template<>
void Parameter<Matrix3x3>::upload()
{
    if(mCPUData)
        glUniformMatrix3fv(mHandle, 1, false, & (mCPUData->elements[0]));
}

template<>
void Parameter<Matrix4x4>::upload()
{
    if(mCPUData)
        glUniformMatrix4fv(mHandle, 1, false, & (mCPUData->elements[0]));
}

template<>
void Parameter<std::vector<int> >::upload()
{
    if(mCPUData)
        glVertexAttribPointer(mHandle, 1, GL_INT, GL_FALSE, 0, & (*mCPUData)[0]);
}

template<>
void Parameter<std::vector<float> >::upload()
{
    if(mCPUData)
        glVertexAttribPointer(mHandle, 2, GL_FLOAT, GL_FALSE, 0, & (*mCPUData)[0]);
}

template<>
void Parameter<std::vector<Vector3> >::upload()
{
    if(mCPUData)
        glVertexAttribPointer(mHandle, 3, GL_FLOAT, GL_FALSE, 0, & (*mCPUData)[0]);
}

template<>
void Parameter<std::vector<Vector4> >::upload()
{
    if(mCPUData)
        glVertexAttribPointer(mHandle, 4, GL_FLOAT, GL_FALSE, 0, & (*mCPUData)[0]);
}
