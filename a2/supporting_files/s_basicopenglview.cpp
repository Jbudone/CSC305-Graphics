#include "basicopenglview.h"

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#ifdef __APPLE__
#include "supporting_files/s_core3_2_context.h"
#endif
#endif

BasicOpenGLView::BasicOpenGLView(QWidget *parent) :
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
#ifdef __APPLE__
    QGLWidget(new Core3_2_context(QGLFormat::defaultFormat()), parent),
#else
    QGLWidget(QGLFormat::defaultFormat(), parent),
#endif
#endif
    mProjectionMatrix(),
    mViewMatrix(),
    mUsePostMultiply(false),
    mGeometries(),
    mFirstFrameDragging(true),
    mLastMousePos()
{
}

void BasicOpenGLView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::map<std::string, Geometry *>::iterator it = mGeometries.begin();

    while (it != mGeometries.end())
    {
        it->second->createModelMatrix(mUsePostMultiply);
        it->second->draw(mProjectionMatrix, mViewMatrix, mUsePostMultiply);
        ++it;
    }

}

void BasicOpenGLView::loadGeometry(std::string m_GeometryPath)
{
    Geometry * newGeometry = new Geometry(m_GeometryPath);
    std::string geometryName = newGeometry->getFileName();

    if(mGeometries.find(geometryName) != mGeometries.end())
    {
        removeGeometry(geometryName);
    }
    mGeometries.insert(std::make_pair(geometryName, newGeometry));

    emit addedNewGeometry(geometryName);
}

void BasicOpenGLView::removeGeometry(std::string m_GeometryFileName)
{
    if(mGeometries.find(m_GeometryFileName) != mGeometries.end())
    {
        delete mGeometries[m_GeometryFileName];
    }
    mGeometries.erase(m_GeometryFileName);

    emit removedGeometry(m_GeometryFileName);
}
