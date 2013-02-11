#include "basicopenglview.h"
#include <QMessageBox>
#include <QtCore>
#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <QMouseEvent>

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

    /**
     *  @todo assignment two
     *  initialize the mViewMatrix and mProjectionMatrix with starting values here
     */

	// default options
	old_transX=old_transY=old_transZ=0;
	mPerspectiveMode=false;
	mUsePostMultiply=false;
	mWorldCrawlerMode=false;

	// projection settings
	fov=90.0f;
	aspect=((float)width())/((float)height());
	plane_near_pers=0.1f;
	plane_far_pers=-4.0f;
	frustum_right=frustum_top=1.5f;
	frustum_left=frustum_bottom=-frustum_right;
	plane_near=2.0f; // NOTE: must be >0
	plane_far=-100.0f;
	
	// initial camera settings
	eye0_arc = Vector3(0.0f, 0.0f, 2.0f);
	at0_arc  = Vector3(0.0f, 0.0f, 0.0f);
	up0_arc  = Vector3(0.0f, 1.0f, 0.0f);

	eye0_fps = Vector3(0.0f, 0.0f, 0.0f);
	at0_fps  = Vector3(0.0f, 0.0f, -1.0f);
	up0_fps  = Vector3(0.0f, 1.0f, 0.0f);

	mMoveScale=0.25; // used for worldcrawler mode
	setFocusPolicy(Qt::StrongFocus); // this allows keypresses to be propagated to this widget


	// Set initial projection
	update_perspective();
	reset_camera();
	mViewMatrix.createView(eye,at,up);
	loadGeometry("3D_objects/cube.obj");
}

void BasicOpenGLView::update_perspective() {
	if (mPerspectiveMode) {
		mProjectionMatrix.projectPerspective(fov,aspect,plane_near_pers,plane_far_pers);
	} else {
		mProjectionMatrix.projectOrthographic(frustum_left,frustum_right,frustum_top,frustum_bottom,plane_near,plane_far);
	}
}

void BasicOpenGLView::reset_camera() {
	if (mWorldCrawlerMode) {
		eye=eye0_fps;
		at=at0_fps;
		up=up0_fps;
	} else {
		eye=eye0_arc;
		at=at0_arc;
		up=up0_arc;
	}
	mViewMatrix.createView(eye,at,up);
}

void BasicOpenGLView::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /**
     *  @todo assignment two
     *  mProjectionMatrix has to be updated in here, when the window is
     *  resized with the values depending on the selected method (orthographic
     *  or perspective)
     *  Hint: for the swap between projection methods to work properly you will also
     *  need to add a function that responds to the switch in the UI
     */
	aspect=((float)width)/((float)height);
	update_perspective();
}

void BasicOpenGLView::mousePressEvent(QMouseEvent *event)
{
    /**
     *  @todo assignment two
     *  these function might be needed for the arc ball or world crawler
     */
	mFirstFrameDragging = true;
}

void BasicOpenGLView::mouseReleaseEvent(QMouseEvent *event)
{
    /**
     *  @todo assignment two
     *  these function might be needed for the arc ball or world crawler
     */
	mFirstFrameDragging = true;
}

void BasicOpenGLView::mouseMoveEvent(QMouseEvent *event)
{
	float eventX = (float)event->x() / width();
    float eventY = 1.0f - (float) event->y() / height();
	
    eventX -= 0.5f;
    eventY -= 0.5f;
    eventX *= 2.0f;
    eventY *= 2.0f;
	
	Vector3 curPoint(eventX, eventY);
	
	if(mFirstFrameDragging)
	{
		mLastMousePos = curPoint;
		mFirstFrameDragging = false;
		return;
	}
	
	Vector3 difference;
	for(size_t i = 0; i < 3; ++i)
	{
		difference.elements[i] = curPoint.elements[i] - mLastMousePos.elements[i];
	}

    /**
     *  @todo assignment two
     *  use the mouse input to modify mViewMatrix to work as an arc-ball interface,
     *  or to rotate the viewer in the XZ plane, depending on the selected mode in the
     *  UI (Arc Ball or World crawler)
     */
	
	Matrix4x4 rotX, rotY;
	float rotScale=fov*3.14f/180.0f; // our rotation diff should be within our fov range (in radians)
	rotY.rotateY(difference.x*rotScale);
	rotX.rotateX(-difference.y*rotScale);
	if (mWorldCrawlerMode) {
		// World Crawler

		// rotate gaze vector by Y
		Vector3 gaze = (at-eye);
		gaze=((Matrix3x3)rotY)*gaze;
		// gaze=((Matrix3x3)(rotY*rotX))*gaze;
		at=eye+gaze;

		// BUG: rotation along the X axis completely broken
		// get new up from gaze rotated 90deg
		// Matrix3x3 rotUp;
		// rotUp=rotUp.rotateX(1.57);
		// gaze=(at-eye);
		// gaze.normalize();
		// up=rotUp*gaze;

		mViewMatrix.createView(eye,at,up);
	} else {
		// Arc-Ball

			// rotate the gaze vector, and apply it to our eye position
			Vector3 gaze, gaze_new, gaze_diff;
			gaze=(at-eye);
			gaze_new=((Matrix3x3)rotX)*gaze;
			// gaze_new=((Matrix3x3)(rotY*rotX))*gaze;
			gaze_diff=gaze_new-gaze;
			eye-=gaze_diff;

			// rotate our new gaze vector by 90deg (so it is perpendicular to our gaze), and apply to our up vec
			// note: we rotate by our current rotation (rotY*rotX) so that we're working within the same space
			Matrix3x3 rotUp;
			// rotUp=((Matrix3x3)(rotY*rotX)).rotateX(1.57);
			rotUp=((Matrix3x3)(rotX)).rotateX(1.57);
			gaze=(at-eye);
			gaze.normalize();
			up=rotUp*gaze;

			// BUG: attempts to include rotX AND rotY together fail
			// gaze=(at-eye);
			// gaze_new=((Matrix3x3)rotY)*gaze;
			// gaze_diff=gaze-gaze_new;
			// printf("gaze_diff (x): "); gaze_diff.print();
			// eye-=gaze_diff;

		mViewMatrix.createView(eye,at,up);
	}
	mLastMousePos = curPoint;
}

void BasicOpenGLView::wheelEvent(QWheelEvent *event) {
	if (!mWorldCrawlerMode) {
		float d=event->delta();
		d/=1200;

		Vector3 forward, left; // what is our current forward/left vectors (relative to where we're facing)
		forward=(at-eye);
		forward.normalize();
		left=(at-eye);
		left=left.cross(up);
		left.normalize();

		eye+=(forward*mMoveVector.z);
		eye-=(left*mMoveVector.x);
		at+=(forward*mMoveVector.z);
		at-=(left*mMoveVector.x);
		mViewMatrix.createView(eye,at,up);


		eye.z+=d;
		mViewMatrix.createView(eye,at,up);
	}
}

void BasicOpenGLView::keyPressEvent(QKeyEvent *event)
{
    /**
     *  @todo assignment two
     *  if World Crawler mode is selected in the UI, use this method to handle
     *  the keyboard input (either arrow keys or WASD) to create the world crawler
     *  movement and create the mViewMatrix for it
     */
	int key=event->key();
	if (mWorldCrawlerMode) {
		switch (key) {
			case Key_Left: case Key_A:
				mMoveVector.x+=mMoveScale;
				break;
			case Key_Up: case Key_W:
				mMoveVector.z+=mMoveScale;
				break;
			case Key_Down: case Key_S:
				mMoveVector.z-=mMoveScale;
				break;
			case Key_Right: case Key_D:
				mMoveVector.x-=mMoveScale;
				break;
		}
	}
}

void BasicOpenGLView::keyReleaseEvent(QKeyEvent *event)
{
    /**
     *  @todo assignment two
     *  if World Crawler mode is selected in the UI, use this method to handle
     *  the keyboard input (either arrow keys or WASD) to create the world crawler
     *  movement and create the mViewMatrix for it
     */
	int key=event->key();
	if (mWorldCrawlerMode) {
		switch (key) {
			case Key_Left: case Key_A:
				mMoveVector.x-=mMoveScale;
				break;
			case Key_Up: case Key_W:
				mMoveVector.z-=mMoveScale;
				break;
			case Key_Down: case Key_S:
				mMoveVector.z+=mMoveScale;
				break;
			case Key_Right: case Key_D:
				mMoveVector.x+=mMoveScale;
				break;
		}
	}
}

void BasicOpenGLView::update_timer() {
	if (mWorldCrawlerMode) {
		Vector3 forward, left; // what is our current forward/left vectors (relative to where we're facing)
		forward=(at-eye);
		forward.normalize();
		left=(at-eye);
		left=left.cross(up);
		left.normalize();

		eye+=(forward*mMoveVector.z);
		eye-=(left*mMoveVector.x);
		at+=(forward*mMoveVector.z);
		at-=(left*mMoveVector.x);
		mViewMatrix.createView(eye,at,up);
	}
}



/*****************************************************************************************/
/** Geometry Manipulation **/


void BasicOpenGLView::translateGeometries_x(int x)
{
	float translate=(float)x/100;
	old_transX=translate;
	printf("Translating x: %f\n", translate);


	// iterate through each geometry to translate
    std::map<std::string, Geometry *>::iterator it = mGeometries.begin();
    while (it != mGeometries.end())
    {
		it->second->translate(Vector3(translate, old_transY, old_transZ));
        ++it;
    }
}

void BasicOpenGLView::translateGeometries_y(int y)
{
	float translate=(float)y/100;
	old_transY=translate;
	printf("Translating y: %f\n", translate);


	// iterate through each geometry to translate
    std::map<std::string, Geometry *>::iterator it = mGeometries.begin();
    while (it != mGeometries.end())
    {
		it->second->translate(Vector3(old_transX, translate, old_transZ));
        ++it;
    }
}

void BasicOpenGLView::translateGeometries_z(int z)
{
	float translate=(float)z/100;
	old_transZ=translate;
	printf("Translating z: %f\n", translate);


	// iterate through each geometry to translate
    std::map<std::string, Geometry *>::iterator it = mGeometries.begin();
    while (it != mGeometries.end())
    {
		it->second->translate(Vector3(old_transX, old_transY, translate));
        ++it;
    }
}

void BasicOpenGLView::scaleGeometries_x(int x)
{
	float scale=(float)x/10;
	printf("Scaling x: %f\n", scale);


	// iterate through each geometry to scale
    std::map<std::string, Geometry *>::iterator it = mGeometries.begin();
    while (it != mGeometries.end())
    {
		it->second->scaleX(scale);
        ++it;
    }
}

void BasicOpenGLView::scaleGeometries_y(int y)
{
	float scale=(float)y/10;
	printf("Scaling y: %f\n", scale);


	// iterate through each geometry to scale
    std::map<std::string, Geometry *>::iterator it = mGeometries.begin();
    while (it != mGeometries.end())
    {
		it->second->scaleY(scale);
        ++it;
    }
}


void BasicOpenGLView::scaleGeometries_z(int z)
{
	float scale=(float)z/10;
	printf("Scaling z: %f\n", scale);


	// iterate through each geometry to scale
    std::map<std::string, Geometry *>::iterator it = mGeometries.begin();
    while (it != mGeometries.end())
    {
		it->second->scaleZ(scale);
        ++it;
    }
}


void BasicOpenGLView::rotateGeometries_x(int x)
{
	float rot=(float)x/100; // max: 2pi, min -2pi (scaled by 100 in UI)
	printf("Rotating x: %f\n", rot);


	// iterate through each geometry to scale
    std::map<std::string, Geometry *>::iterator it = mGeometries.begin();
    while (it != mGeometries.end())
    {
		it->second->rotateX(rot);
        ++it;
    }
}

void BasicOpenGLView::rotateGeometries_y(int y)
{
	float rot=(float)y/100; // max: 2pi, min -2pi (scaled by 100 in UI)
	printf("Rotating y: %f\n", rot);


	// iterate through each geometry to scale
    std::map<std::string, Geometry *>::iterator it = mGeometries.begin();
    while (it != mGeometries.end())
    {
		it->second->rotateY(rot);
        ++it;
    }
}

void BasicOpenGLView::rotateGeometries_z(int z)
{
	float rot=(float)z/100; // max: 2pi, min -2pi (scaled by 100 in UI)
	printf("Rotating z: %f\n", rot);


	// iterate through each geometry to scale
    std::map<std::string, Geometry *>::iterator it = mGeometries.begin();
    while (it != mGeometries.end())
    {
		it->second->rotateZ(rot);
        ++it;
    }
}

void BasicOpenGLView::option_worldCrawler(bool checked) {
	mWorldCrawlerMode=checked;
	reset_camera();
}
void BasicOpenGLView::option_perspective(bool checked) {
	mPerspectiveMode=checked;
	update_perspective();
}
void BasicOpenGLView::option_postMultiply(bool checked) {
	mUsePostMultiply=checked;
}

