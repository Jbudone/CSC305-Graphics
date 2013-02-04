#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    animationTimer(NULL)
{
    ui->setupUi(this);

    // we create a simple timer, with the widget being its parent
    animationTimer = new QTimer(this);
    // the timer will send a signal timeout at regular intervals.
    // whenever this timeout signal occurs, we want it to call our drawOpenGL
    // function
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(drawOpenGL()));
    // we start the timer with a timeout interval of 20ms
    animationTimer->start(20);

    connect(ui->oglwidget, SIGNAL(addedNewGeometry(std::string)), this, SLOT(newGeometryAdded(std::string)));
    connect(ui->oglwidget, SIGNAL(removedGeometry(std::string)), this, SLOT(geometryRemoved(std::string)));

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addGeometry()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(removeGeometry()));

	// (JB)
	// Connect the geometry manipulation sliders
	connect(ui->slide_transx, SIGNAL(valueChanged(int)), this, SLOT(translateGeometries_x(int)));
	connect(ui->slide_transy, SIGNAL(valueChanged(int)), this, SLOT(translateGeometries_y(int)));
	connect(ui->slide_transz, SIGNAL(valueChanged(int)), this, SLOT(translateGeometries_z(int)));

	connect(ui->slide_scalex, SIGNAL(valueChanged(int)), this, SLOT(scaleGeometries_x(int)));
	connect(ui->slide_scaley, SIGNAL(valueChanged(int)), this, SLOT(scaleGeometries_y(int)));
	connect(ui->slide_scalez, SIGNAL(valueChanged(int)), this, SLOT(scaleGeometries_z(int)));

	connect(ui->slide_rotx, SIGNAL(valueChanged(int)), this, SLOT(rotateGeometries_x(int)));
	connect(ui->slide_roty, SIGNAL(valueChanged(int)), this, SLOT(rotateGeometries_y(int)));
	connect(ui->slide_rotz, SIGNAL(valueChanged(int)), this, SLOT(rotateGeometries_z(int)));
}

void MainWindow::drawOpenGL()
{
    // whenever drawOpenGL gets called, we only want to repaint our opengl widget
    ui->oglwidget->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::translateGeometries_x(int x)
{
	printf("Translating: %i\n", x);


	// iterate through each geometry to translate
    std::map<std::string, Geometry *>::iterator it = mGeometries.begin();
    while (it != mGeometries.end())
    {
		it->second->translate(Vector3(x, 0, 0));
        ++it;
    }
}

void MainWindow::translateGeometries_y(int y)
{
	printf("Translating: %i\n", y);
}

void MainWindow::translateGeometries_z(int z)
{
	printf("Translating: %i\n", z);
}

void MainWindow::scaleGeometries_x(int x)
{
	printf("Scaling: %i\n", x);
}

void MainWindow::scaleGeometries_y(int y)
{
	printf("Scaling: %i\n", y);
}


void MainWindow::scaleGeometries_z(int z)
{
	printf("Scaling: %i\n", z);
}


void MainWindow::rotateGeometries_x(int x)
{
	printf("Rotating: %i\n", x);
}

void MainWindow::rotateGeometries_y(int y)
{
	printf("Rotating: %i\n", y);
}

void MainWindow::rotateGeometries_z(int z)
{
	printf("Rotating: %i\n", z);
}

