/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Feb 3 11:30:45 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "basicopenglview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdd_Model;
    QAction *actionRemove_Selected;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    BasicOpenGLView *oglwidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupModels;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QPushButton *addButton;
    QPushButton *removeButton;
    QGroupBox *groupTranslation;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QSlider *slide_transx;
    QSlider *slide_transy;
    QSlider *slide_transz;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QGroupBox *groupRotation;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_6;
    QSlider *slide_rotx;
    QSlider *slide_roty;
    QSlider *slide_rotz;
    QGroupBox *groupScale;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QWidget *layoutWidget_4;
    QVBoxLayout *verticalLayout_8;
    QSlider *slide_scalex;
    QSlider *slide_scaley;
    QSlider *slide_scalez;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(770, 798);
        MainWindow->setMaximumSize(QSize(770, 16777215));
        actionAdd_Model = new QAction(MainWindow);
        actionAdd_Model->setObjectName(QString::fromUtf8("actionAdd_Model"));
        actionRemove_Selected = new QAction(MainWindow);
        actionRemove_Selected->setObjectName(QString::fromUtf8("actionRemove_Selected"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        oglwidget = new BasicOpenGLView(centralWidget);
        oglwidget->setObjectName(QString::fromUtf8("oglwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(oglwidget->sizePolicy().hasHeightForWidth());
        oglwidget->setSizePolicy(sizePolicy);
        oglwidget->setMinimumSize(QSize(400, 300));

        horizontalLayout->addWidget(oglwidget);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMinimumSize(QSize(250, 0));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 0, -1, 0);
        groupModels = new QGroupBox(groupBox);
        groupModels->setObjectName(QString::fromUtf8("groupModels"));
        groupModels->setEnabled(true);
        groupModels->setMinimumSize(QSize(230, 0));
        groupModels->setMaximumSize(QSize(230, 16777215));
        verticalLayout = new QVBoxLayout(groupModels);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 9, -1, -1);
        listWidget = new QListWidget(groupModels);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy2);
        listWidget->setMinimumSize(QSize(200, 300));
        listWidget->setMaximumSize(QSize(200, 16777215));
        listWidget->setAlternatingRowColors(true);
        listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidget->setSelectionRectVisible(true);

        verticalLayout->addWidget(listWidget);

        addButton = new QPushButton(groupModels);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        verticalLayout->addWidget(addButton);

        removeButton = new QPushButton(groupModels);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));

        verticalLayout->addWidget(removeButton);


        verticalLayout_2->addWidget(groupModels, 0, Qt::AlignTop);

        groupTranslation = new QGroupBox(groupBox);
        groupTranslation->setObjectName(QString::fromUtf8("groupTranslation"));
        groupTranslation->setAutoFillBackground(true);
        widget = new QWidget(groupTranslation);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 20, 191, 61));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        slide_transx = new QSlider(widget);
        slide_transx->setObjectName(QString::fromUtf8("slide_transx"));
        sizePolicy2.setHeightForWidth(slide_transx->sizePolicy().hasHeightForWidth());
        slide_transx->setSizePolicy(sizePolicy2);
        slide_transx->setMinimumSize(QSize(0, 5));
        slide_transx->setMaximumSize(QSize(16777215, 20));
        slide_transx->setValue(0);
        slide_transx->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(slide_transx);

        slide_transy = new QSlider(widget);
        slide_transy->setObjectName(QString::fromUtf8("slide_transy"));
        sizePolicy2.setHeightForWidth(slide_transy->sizePolicy().hasHeightForWidth());
        slide_transy->setSizePolicy(sizePolicy2);
        slide_transy->setMinimumSize(QSize(0, 5));
        slide_transy->setMaximumSize(QSize(16777215, 20));
        slide_transy->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(slide_transy);

        slide_transz = new QSlider(widget);
        slide_transz->setObjectName(QString::fromUtf8("slide_transz"));
        sizePolicy2.setHeightForWidth(slide_transz->sizePolicy().hasHeightForWidth());
        slide_transz->setSizePolicy(sizePolicy2);
        slide_transz->setMinimumSize(QSize(0, 5));
        slide_transz->setMaximumSize(QSize(16777215, 20));
        slide_transz->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(slide_transz);

        widget1 = new QWidget(groupTranslation);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(10, 20, 12, 65));
        verticalLayout_4 = new QVBoxLayout(widget1);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("text-weight:bold;"));

        verticalLayout_4->addWidget(label);

        label_2 = new QLabel(widget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("text-weight:bold;"));

        verticalLayout_4->addWidget(label_2);

        label_3 = new QLabel(widget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("text-weight:bold;"));

        verticalLayout_4->addWidget(label_3);

        label->raise();

        verticalLayout_2->addWidget(groupTranslation);

        groupRotation = new QGroupBox(groupBox);
        groupRotation->setObjectName(QString::fromUtf8("groupRotation"));
        groupRotation->setAutoFillBackground(true);
        layoutWidget = new QWidget(groupRotation);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 12, 65));
        verticalLayout_5 = new QVBoxLayout(layoutWidget);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("text-weight:bold;"));

        verticalLayout_5->addWidget(label_4);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("text-weight:bold;"));

        verticalLayout_5->addWidget(label_5);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("text-weight:bold;"));

        verticalLayout_5->addWidget(label_6);

        layoutWidget_2 = new QWidget(groupRotation);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(30, 20, 191, 61));
        verticalLayout_6 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        slide_rotx = new QSlider(layoutWidget_2);
        slide_rotx->setObjectName(QString::fromUtf8("slide_rotx"));
        sizePolicy2.setHeightForWidth(slide_rotx->sizePolicy().hasHeightForWidth());
        slide_rotx->setSizePolicy(sizePolicy2);
        slide_rotx->setMinimumSize(QSize(0, 5));
        slide_rotx->setMaximumSize(QSize(16777215, 20));
        slide_rotx->setValue(0);
        slide_rotx->setOrientation(Qt::Horizontal);

        verticalLayout_6->addWidget(slide_rotx);

        slide_roty = new QSlider(layoutWidget_2);
        slide_roty->setObjectName(QString::fromUtf8("slide_roty"));
        sizePolicy2.setHeightForWidth(slide_roty->sizePolicy().hasHeightForWidth());
        slide_roty->setSizePolicy(sizePolicy2);
        slide_roty->setMinimumSize(QSize(0, 5));
        slide_roty->setMaximumSize(QSize(16777215, 20));
        slide_roty->setOrientation(Qt::Horizontal);

        verticalLayout_6->addWidget(slide_roty);

        slide_rotz = new QSlider(layoutWidget_2);
        slide_rotz->setObjectName(QString::fromUtf8("slide_rotz"));
        sizePolicy2.setHeightForWidth(slide_rotz->sizePolicy().hasHeightForWidth());
        slide_rotz->setSizePolicy(sizePolicy2);
        slide_rotz->setMinimumSize(QSize(0, 5));
        slide_rotz->setMaximumSize(QSize(16777215, 20));
        slide_rotz->setOrientation(Qt::Horizontal);

        verticalLayout_6->addWidget(slide_rotz);

        layoutWidget->raise();
        layoutWidget_2->raise();

        verticalLayout_2->addWidget(groupRotation);

        groupScale = new QGroupBox(groupBox);
        groupScale->setObjectName(QString::fromUtf8("groupScale"));
        groupScale->setEnabled(true);
        groupScale->setAutoFillBackground(true);
        layoutWidget_3 = new QWidget(groupScale);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 20, 12, 65));
        verticalLayout_7 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(layoutWidget_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("text-weight:bold;"));

        verticalLayout_7->addWidget(label_7);

        label_8 = new QLabel(layoutWidget_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setStyleSheet(QString::fromUtf8("text-weight:bold;"));

        verticalLayout_7->addWidget(label_8);

        label_9 = new QLabel(layoutWidget_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setStyleSheet(QString::fromUtf8("text-weight:bold;"));

        verticalLayout_7->addWidget(label_9);

        layoutWidget_4 = new QWidget(groupScale);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(30, 20, 191, 61));
        verticalLayout_8 = new QVBoxLayout(layoutWidget_4);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        slide_scalex = new QSlider(layoutWidget_4);
        slide_scalex->setObjectName(QString::fromUtf8("slide_scalex"));
        sizePolicy2.setHeightForWidth(slide_scalex->sizePolicy().hasHeightForWidth());
        slide_scalex->setSizePolicy(sizePolicy2);
        slide_scalex->setMinimumSize(QSize(0, 5));
        slide_scalex->setMaximumSize(QSize(16777215, 20));
        slide_scalex->setValue(0);
        slide_scalex->setOrientation(Qt::Horizontal);

        verticalLayout_8->addWidget(slide_scalex);

        slide_scaley = new QSlider(layoutWidget_4);
        slide_scaley->setObjectName(QString::fromUtf8("slide_scaley"));
        sizePolicy2.setHeightForWidth(slide_scaley->sizePolicy().hasHeightForWidth());
        slide_scaley->setSizePolicy(sizePolicy2);
        slide_scaley->setMinimumSize(QSize(0, 5));
        slide_scaley->setMaximumSize(QSize(16777215, 20));
        slide_scaley->setOrientation(Qt::Horizontal);

        verticalLayout_8->addWidget(slide_scaley);

        slide_scalez = new QSlider(layoutWidget_4);
        slide_scalez->setObjectName(QString::fromUtf8("slide_scalez"));
        sizePolicy2.setHeightForWidth(slide_scalez->sizePolicy().hasHeightForWidth());
        slide_scalez->setSizePolicy(sizePolicy2);
        slide_scalez->setMinimumSize(QSize(0, 5));
        slide_scalez->setMaximumSize(QSize(16777215, 20));
        slide_scalez->setOrientation(Qt::Horizontal);

        verticalLayout_8->addWidget(slide_scalez);


        verticalLayout_2->addWidget(groupScale);


        horizontalLayout->addWidget(groupBox, 0, Qt::AlignRight);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 770, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionAdd_Model);
        menuEdit->addAction(actionRemove_Selected);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionAdd_Model->setText(QApplication::translate("MainWindow", "Add Model...", 0, QApplication::UnicodeUTF8));
        actionRemove_Selected->setText(QApplication::translate("MainWindow", "Remove Selected", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        groupModels->setTitle(QApplication::translate("MainWindow", "Models", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("MainWindow", "Add...", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        groupTranslation->setTitle(QApplication::translate("MainWindow", "Translation", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "x", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "y", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "z", 0, QApplication::UnicodeUTF8));
        groupRotation->setTitle(QApplication::translate("MainWindow", "Rotation", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "x", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "y", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "z", 0, QApplication::UnicodeUTF8));
        groupScale->setTitle(QApplication::translate("MainWindow", "Scale", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "x", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "y", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "z", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
