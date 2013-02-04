#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QListWidgetItem>

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
     *  @todo   assignment 1
     *  add the connection of the slider with the appropriate slot in this class
     */
    connect(ui->scaleSlider, SIGNAL(valueChanged(int)), this, SLOT(scaleGeometry(int)));
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

void MainWindow::newGeometryAdded(std::string m_GeometryName)
{
    ui->listWidget->addItem(QString(m_GeometryName.c_str()));
}

void MainWindow::geometryRemoved(std::string m_GeometryName)
{
    QString geometryName(m_GeometryName.c_str());
    QList<QListWidgetItem *> items = ui->listWidget->findItems(geometryName, Qt::MatchFixedString);

    QList<QListWidgetItem *>::iterator it = items.begin();

    while(it != items.end())
    {
        delete ui->listWidget->takeItem(ui->listWidget->row((*it)));
        ++it;
    }
}

void MainWindow::addGeometry()
{
    this->on_actionAdd_Model_triggered();
}

void MainWindow::removeGeometry()
{
    this->on_actionRemove_Selected_triggered();
}

void MainWindow::on_actionAdd_Model_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Files (*.obj)"));

    if(!fileName.isNull())
        ui->oglwidget->loadGeometry(fileName.toStdString());
}

void MainWindow::on_actionRemove_Selected_triggered()
{
    QList<QListWidgetItem *> items = ui->listWidget->selectedItems();
    QList<QListWidgetItem *>::iterator it = items.begin();

    while(it != items.end())
    {
        ui->oglwidget->removeGeometry((*it)->text().toStdString());
        ++it;
    }
}

void MainWindow::scaleGeometry(int sliderValue)
{
    ui->oglwidget->scaleGeometries(((float)sliderValue)/100.0f);
}
