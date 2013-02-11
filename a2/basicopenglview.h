#ifndef BASICOPENGLVIEW_H
#define BASICOPENGLVIEW_H

#ifndef __APPLE__
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <QGLWidget>
#include <QMatrix4x4>
#include "geometry.h"

using namespace Qt;

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

    /**
     * keyPressEvent is called when the window has focus and a key on the
     * keyboard is pressed
     * @param event
     */
    void keyPressEvent ( QKeyEvent * event );

    /**
     * keyReleaseEvent is called when the window has focus and a key on the
     * keyboard is released
     * @param event
     */
    void keyReleaseEvent ( QKeyEvent * event );


	/**
	 * mouseScrollEvent called when mouse wheel scrolled
	 */
	void wheelEvent(QWheelEvent *event);



public slots:
	/**************************************************************************************/
	/** Geometry Manipulation **/

	/**
	 * Translations
	 * Translate the geometry for each component
	 */
	void translateGeometries_x(int);
	void translateGeometries_y(int);
	void translateGeometries_z(int);

	/**
	 * Scaling
	 * Scale the geometries for each component
	 */
	void scaleGeometries_x(int);
	void scaleGeometries_y(int);
	void scaleGeometries_z(int);

	/**
	 * Rotation
	 * Rotate the geometries for each component
	 */
	void rotateGeometries_x(int);
	void rotateGeometries_y(int);
	void rotateGeometries_z(int);

	/**
	 * Options
	 * Change options here
	 */
	void option_worldCrawler(bool);
	void option_perspective(bool);
	void option_postMultiply(bool);
	void update_perspective(); // triggered whenever perspective mode switches
	void reset_camera(); // triggered whenever we switch between camera mode (fps/arcball)

	void update_timer();

private:

    Matrix4x4       mProjectionMatrix;              /**< the projection matrix to be used for rendering. */
    Matrix4x4       mViewMatrix;                    /**< the view matrix to be used for rendering. */
    bool            mUsePostMultiply;               /**< if the post multiply has to be used for the matrices. */
	bool			mWorldCrawlerMode;				/**< if camera movement works in world crawler mode. */
	bool			mPerspectiveMode;				/**< if we're using the perspective view. */
    std::map<std::string, Geometry *>   mGeometries;    /**< the map containing the filename of the geometry as key, and the pointer to the geometry as value. */
	
	bool	mFirstFrameDragging;			/**< if we are in the first dragging frame. */
	Vector3	mLastMousePos;					/**< the last mouse position while dragging. */
	float old_transX, old_transY, old_transZ; // old storage values of translations
	Vector3 mMoveVector;					/**< the vector in which we're currently moving (from keydown). */
	float mMoveScale;						/**< scaling the move vector in worldcrawler mode */
	float fov;								/** < field of view. */
	float aspect;							/** < aspect ratio. */
	float plane_near, plane_far;			/** < near and far plane values. */
	float plane_near_pers, plane_far_pers;
	float frustum_top, frustum_bottom, frustum_left, frustum_right; /** < view frustum values. */
	Vector3 eye, at, up; // current eye/at/up
	Vector3 eye0_fps, at0_fps, up0_fps; // initial eye/at/up in fps (worldcrawler mode)
	Vector3 eye0_arc, at0_arc, up0_arc; // initial eye/at/up in arcball mode
};

#endif // BASICOPENGLVIEW_H
