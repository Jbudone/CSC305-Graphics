#include "basicopenglview.h"
#include <QMessageBox>
#include <QtCore>
#include <iostream>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif
#include <QMouseEvent>

BasicOpenGLView::BasicOpenGLView(QWidget *parent) :
    #if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    #ifdef __APPLE__
    QGLWidget(new Core3_2_context(QGLFormat::defaultFormat()), parent),
    #else
    QGLWidget(QGLFormat::defaultFormat(), parent),
    #endif
    #endif
    mGeometries()
{
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

void BasicOpenGLView::scaleGeometries(float m_ScaleFactor)
{
    /**
     *  @todo   assignment 1
     *  loop over all geometries and scale them
     */

	// printf("scale: %f\n",m_ScaleFactor);
	std::map<std::string, Geometry *>::iterator it = mGeometries.begin();
    while (it != mGeometries.end())
    {
		it->second->scale(m_ScaleFactor);
        ++it;
    }
}

void BasicOpenGLView::initializeGL()
{
#ifndef __APPLE__
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cerr << "Glew could not initialize" << std::endl;
    }
#endif
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    std::cout<<glGetString(GL_VERSION)<<std::endl;
#else
    if(this->format().majorVersion() < 3 && this->format().minorVersion() < 2)
    {
        QMessageBox msgBox;
        msgBox.setText("The OpenGL version available on this computer is too old.");
        msgBox.setInformativeText("OpenGL 3.2 or higher required to run this application.");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Close);
        msgBox.setDefaultButton(QMessageBox::Close);
        msgBox.exec();
        QCoreApplication::quit();
    }
#endif

}

void BasicOpenGLView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::map<std::string, Geometry *>::iterator it = mGeometries.begin();

    while (it != mGeometries.end())
    {
        it->second->draw();
        ++it;
    }

}

void BasicOpenGLView::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void BasicOpenGLView::mousePressEvent(QMouseEvent *event)
{
    // TODO deal with mouse buttons
    mFirstFrameDragging = true;
}

void BasicOpenGLView::mouseReleaseEvent(QMouseEvent *event)
{
    mFirstFrameDragging = true;
}

void BasicOpenGLView::mouseMoveEvent(QMouseEvent *event)
{
    /**
     *  @todo    assignment 1
     *  convert the mouse event coordinate into OpenGL view coordinates.
     *  store them in curPoint.
     */


	QPointF pt = event->posF();
    Vector3 curPoint;
	
	// interpolate position to opengl screen coords [-1,1]
	curPoint.x = ((pt.x() * 2) / width()) - 1;
	curPoint.y = ((pt.y() * 2) / height()) - 1;

	// do not allow points to go outside of coordinate system [-1,1] 
	if (curPoint.x < -1) curPoint.x=-1;
	if (curPoint.x > 1)  curPoint.x=1;
	if (curPoint.y < -1) curPoint.y=-1;
	if (curPoint.y > 1)  curPoint.y=1;
	// printf("x: %f, y: %f\n",curPoint.x,curPoint.y);

    // to avoid jumping when a new drag started, we check if this is our first dragging frame
    // in that case we only store our current mouse position
    if(mFirstFrameDragging)
    {
        mLastMousePos = curPoint;
        mFirstFrameDragging = false;
        return;
    }

    /**
     *  @todo   assignment 1
     *  calculate the difference the mouse has moved in OpenGL coordinates between this frame and
     *  the previous.
     *  translate all geometries accordingly
     */

	// iterate through each geometry to translate
    std::map<std::string, Geometry *>::iterator it = mGeometries.begin();
    while (it != mGeometries.end())
    {
		it->second->translate(Vector3(mLastMousePos.x - curPoint.x, mLastMousePos.y - curPoint.y, mLastMousePos.z - curPoint.z));
        ++it;
    }
    mLastMousePos = curPoint;
}
