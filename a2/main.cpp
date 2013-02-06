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
	// TODO: test the fact that operator+ changes lhs   (matc = mata + matb  ; does mata change?)

	/*
	Matrix3x3 matA;
	matA[0]=1; matA[3]=2; matA[6]=3;
	matA[1]=4; matA[4]=5; matA[7]=6;
	matA[2]=7; matA[5]=8; matA[8]=9;
	Matrix3x3 matB;
	matB[0]=1; matB[3]=2; matB[6]=3;
	matB[1]=4; matB[4]=5; matB[7]=6;
	matB[2]=7; matB[5]=8; matB[8]=9;
	Matrix3x3 matC;

	matC = matA + matB;
	matA.print();
	matC.print();
// 
// 	Matrix4x4 mat = (((Matrix4x4)( matA ) + (Matrix4x4)( matB )) - ((Matrix4x4)( matB ) * 2)) * 15;
// 	mat *= 3;
// 	mat += (Matrix4x4)matC;
// 	mat.print();
// 	mat *= ((Matrix4x4)matC * 5);
// 	mat.print();
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
