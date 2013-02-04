#ifndef BASICOPENGLVIEW_H
#define BASICOPENGLVIEW_H

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <QGLWidget>
#include <QMatrix4x4>
#include "geometry.h"

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#ifdef __APPLE__
#include <QGLContext>

void* select_3_2_mac_visual(GDHandle handle);


struct Core3_2_context : public QGLContext
{
	Core3_2_context(const QGLFormat& format, QPaintDevice* device) : QGLContext(format,device) {}
	Core3_2_context(const QGLFormat& format) : QGLContext(format) {}
	
    virtual void* chooseMacVisual(GDHandle handle)
	{
		return select_3_2_mac_visual(handle);
	}
};
#endif
#endif

/**
  * @class  BasicOpenGLView
  * @brief  our OpenGL view derived from QGLWidget.
  * We have to override several functions for our
  * application-specific OpenGL drawing functionality
  */
class BasicOpenGLView : public QGLWidget
{
    /**
      * macro needed to be inserted in every QT derived class.
      */
    Q_OBJECT
public:

    /**
      * our constructor
      * @param  parent the parent object of the widget.
                pass this one on to the superclass constructor
      */
    explicit BasicOpenGLView(QWidget *parent = 0);

    /**
     * @brief loadGeometry
     * loads the geometry at the given path
     * @param m_GeometryPath the full path to the geometry file
     */
    void loadGeometry(std::string m_GeometryPath);

    /**
     * @brief removeGeometry
     * removes all occurences of the geometry with the given filename
     * @param m_GeometryFileName the filename of the geometry
     */
    void removeGeometry(std::string m_GeometryFileName);

    /**
     * @brief scaleGeometries
     * @param m_ScaleFactor the new scale factor
     */
    void scaleGeometries(float m_ScaleFactor);

signals:

    /**
     * @brief addedNewGeometry
     * signal is emitted when a new geometry is added to the scene
     * @param m_GeometryName the name of the geometry
     */
    void addedNewGeometry(std::string m_GeometryName);

    /**
     * @brief removedGeometry
     * signal is emitted when a geometry object is removed from the scene
     * @param m_GeometryName the name of the geometry
     */
    void removedGeometry(std::string m_GeometryName);

public slots:

protected:

    /**
      * function called automatically by QT after the OpenGL context is created
      * in here, do all OpenGL setup stuff, that you can before the actual program
      * execution starts
      */
    void initializeGL();

    /**
      * the function called whenever our Widget is being redrawn.
      * assume that the BasicOpenGLView's OpenGL context has already
      * been made the current one, so no need to call
      * this->makeCurrent(); anymore
      * Do all your rendering loop related code in there
      */
    void paintGL();

    /**
      * method called when the widget is resized.
      * we need code in there, to react to the changed window size
      * otherwise the rendering will look skewed and ugly
      */
    void resizeGL(int width, int height);

    /**
      * function called when a mouse button is pressed and the cursor is hovering
      * over our widget
      * use the QMouseEvent classmembers to access the mouse information
      */
    void mousePressEvent(QMouseEvent *event);
	
	/**
	 * function called when a mouse button is released and/or the cursor stopped hovering
	 * over our widget
	 * use the QMouseEvent classmembers to access the mouse information
	 */
	void mouseReleaseEvent(QMouseEvent *event);

    /**
      * function called when mouse cursor is moved inside our widgets region
      * use the QMouseEvent classmembers to access the mouse information
      */
    void mouseMoveEvent(QMouseEvent *event);

private:

    std::map<std::string, Geometry *>   mGeometries;    /**< the map containing the filename of the geometry as key, and the pointer to the geometry as value. */
	
	bool	mFirstFrameDragging;			/**< if we are in the first dragging frame. */
	Vector3	mLastMousePos;					/**< the last mouse position while dragging. */
};

#endif // BASICOPENGLVIEW_H
