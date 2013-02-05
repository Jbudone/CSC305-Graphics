#include "geometry.h"

Geometry::Geometry() : mFileName(),
    mFilePath(),
    mModelMatrix(),
    mColorBuffer(0),
    mNormalBuffer(0),
    mTexCoordBuffer(0),
    mVertexBuffer(0),
    mVertexArray(0),
    mPrimitiveType(POINTS),
    mVertices(),
    mNormals(),
    mTexCoords(),
    mColors(),
    mScaleFactor(1.0f)

{
    initOpenGLBuffers();

    initDefaultShader();
}

Geometry::Geometry(std::string m_FilePath) : mFileName(),
    mFilePath(m_FilePath),
    mColorBuffer(0),
    mNormalBuffer(0),
    mTexCoordBuffer(0),
    mVertexBuffer(0),
    mVertexArray(0),
    mPrimitiveType(POINTS),
    mVertices(),
    mNormals(),
    mTexCoords(),
    mColors(),
    mScaleFactor(1.0f)

{
    initOpenGLBuffers();

    initDefaultShader();

    this->parseFile();
}

void Geometry::translate(Vector3 m_Translation)
{
    /**
     *  @todo assignment two
     *  add the new translation to the old one
     */
	translation[6]=m_Translation.x;
	translation[7]=m_Translation.y;
	translation[8]=m_Translation.z;
}

void Geometry::scaleX(float m_ScaleFactor)
{
    /**
     *  @todo assignment two
     *  add the new scale x to the old one
     */
	scale[0]=m_ScaleFactor;
}

void Geometry::scaleY(float m_ScaleFactor)
{
    /**
     *  @todo assignment two
     *  add the new scale y to the old one
     */
	scale[4]=m_ScaleFactor;
}

void Geometry::scaleZ(float m_ScaleFactor)
{
    /**
     *  @todo assignment two
     *  add the new scale z to the old one
     */
	scale[8]=m_ScaleFactor;
}

void Geometry::rotateX(float m_Degrees)
{
    /**
     *  @todo assignment two
     *  add the new rotate x to the old one
     */
	rotationX[0]=1;
	rotationX[4]=cos(m_Degrees);
	rotationX[8]=cos(m_Degrees);
	rotationX[7]=-sin(m_Degrees);
	rotationX[5]=sin(m_Degrees);
}

void Geometry::rotateY(float m_Degrees)
{
    /**
     *  @todo assignment two
     *  add the new rotate y to the old one
     */
	rotationY[4]=1;
	rotationY[0]=cos(m_Degrees);
	rotationY[8]=cos(m_Degrees);
	rotationY[2]=-sin(m_Degrees);
	rotationY[6]=sin(m_Degrees);
}

void Geometry::rotateZ(float m_Degrees)
{
    /**
     *  @todo assignment two
     *  add the new rotate z to the old one
     */
	rotationZ[8]=1;
	rotationZ[0]=cos(m_Degrees);
	rotationZ[4]=cos(m_Degrees);
	rotationZ[3]=-sin(m_Degrees);
	rotationZ[1]=sin(m_Degrees);
}

void Geometry::createModelMatrix(bool m_UsePostMultiply)
{
    /**
     *  @todo assignment two
     * create the model matrix based on the translate, scale and rotation values
     * stored as class members.
     * @param m_UsePostMultiply defines if the single transformation matrices have to be
     * premultiplied or postmultiplied to build the final transformation matrix.
     * store the matrix in mModelMatrix
     */

	// NOTE TO SELF: translate * rotate * scale
}
