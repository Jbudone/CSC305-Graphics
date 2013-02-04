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

	/**
	 * Connecting signals and slots for UI
	 * Connect the geometry manipulation sliders
	 */
	connect(ui->slide_transx, SIGNAL(valueChanged(int)), ui->oglwidget, SLOT(translateGeometries_x(int)));
	connect(ui->slide_transy, SIGNAL(valueChanged(int)), ui->oglwidget, SLOT(translateGeometries_y(int)));
	connect(ui->slide_transz, SIGNAL(valueChanged(int)), ui->oglwidget, SLOT(translateGeometries_z(int)));

	connect(ui->slide_scalex, SIGNAL(valueChanged(int)), ui->oglwidget, SLOT(scaleGeometries_x(int)));
	connect(ui->slide_scaley, SIGNAL(valueChanged(int)), ui->oglwidget, SLOT(scaleGeometries_y(int)));
	connect(ui->slide_scalez, SIGNAL(valueChanged(int)), ui->oglwidget, SLOT(scaleGeometries_z(int)));

	connect(ui->slide_rotx, SIGNAL(valueChanged(int)), ui->oglwidget, SLOT(rotateGeometries_x(int)));
	connect(ui->slide_roty, SIGNAL(valueChanged(int)), ui->oglwidget, SLOT(rotateGeometries_y(int)));
	connect(ui->slide_rotz, SIGNAL(valueChanged(int)), ui->oglwidget, SLOT(rotateGeometries_z(int)));
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

