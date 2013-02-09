#include <QtGui/QApplication>
#ifndef __APPLE__
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#include <QGLFormat>
#include "mainwindow.h"

#include "matrix.cpp"

int main(int argc, char *argv[])
{
	/***************************************************/
	/** Matrix Algebra testing **/

	// NOTE: This is left here for testing needs
	/*
	Matrix3x3 matA;
	matA[0]=0.1; matA[3]=0.2; matA[6]=0.3;
	matA[1]=0.4; matA[4]=0.5; matA[7]=0.6;
	matA[2]=0.7; matA[5]=0.8; matA[8]=0.9;
	Matrix3x3 matB;
	matB[0]=1.1; matB[3]=1.2; matB[6]=1.3;
	matB[1]=1.4; matB[4]=1.5; matB[7]=1.6;
	matB[2]=1.7; matB[5]=1.8; matB[8]=1.9;
	Matrix3x3 matC;

	matC = matA * matB * matC * 2 * matA;

	matA.print();
	matB.print();
	matC.print();
	return 0;
	*/
	
	

    QApplication a(argc, argv);

    // Specify an OpenGL 3.2 format using the Core profile.
    // That is, no old-school fixed pipeline functionality
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
    QGLFormat glFormat;
    glFormat.setVersion( 3, 2 );
    glFormat.setProfile( QGLFormat::CoreProfile ); // Requires >=Qt-4.8.0
    glFormat.setSampleBuffers( true );

    QGLFormat::setDefaultFormat(glFormat);
#endif

    MainWindow w;
    w.show();
    
    return a.exec();
}
