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
	mModelMatrix.elements[12]+=m_Translation.x;
}

void Geometry::scaleX(float m_ScaleFactor)
{
    /**
     *  @todo assignment two
     *  add the new scale x to the old one
     */
}

void Geometry::scaleY(float m_ScaleFactor)
{
    /**
     *  @todo assignment two
     *  add the new scale y to the old one
     */
}

void Geometry::scaleZ(float m_ScaleFactor)
{
    /**
     *  @todo assignment two
     *  add the new scale z to the old one
     */
}

void Geometry::rotateX(float m_Degrees)
{
    /**
     *  @todo assignment two
     *  add the new rotate x to the old one
     */
}

void Geometry::rotateY(float m_Degrees)
{
    /**
     *  @todo assignment two
     *  add the new rotate y to the old one
     */
}

void Geometry::rotateZ(float m_Degrees)
{
    /**
     *  @todo assignment two
     *  add the new rotate z to the old one
     */
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
}
