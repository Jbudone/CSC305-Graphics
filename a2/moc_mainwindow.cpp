/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sun Feb 3 12:52:50 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      40,   25,   11,   11, 0x0a,
      70,   25,   11,   11, 0x0a,
      99,   11,   11,   11, 0x0a,
     113,   11,   11,   11, 0x0a,
     130,   11,   11,   11, 0x0a,
     157,   11,   11,   11, 0x0a,
     184,   11,   11,   11, 0x0a,
     211,   11,   11,   11, 0x0a,
     234,   11,   11,   11, 0x0a,
     257,   11,   11,   11, 0x0a,
     280,   11,   11,   11, 0x0a,
     304,   11,   11,   11, 0x0a,
     328,   11,   11,   11, 0x0a,
     352,   11,   11,   11, 0x08,
     383,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0drawOpenGL()\0m_GeometryName\0"
    "newGeometryAdded(std::string)\0"
    "geometryRemoved(std::string)\0addGeometry()\0"
    "removeGeometry()\0translateGeometries_x(int)\0"
    "translateGeometries_y(int)\0"
    "translateGeometries_z(int)\0"
    "scaleGeometries_x(int)\0scaleGeometries_y(int)\0"
    "scaleGeometries_z(int)\0rotateGeometries_x(int)\0"
    "rotateGeometries_y(int)\0rotateGeometries_z(int)\0"
    "on_actionAdd_Model_triggered()\0"
    "on_actionRemove_Selected_triggered()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->drawOpenGL(); break;
        case 1: _t->newGeometryAdded((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 2: _t->geometryRemoved((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 3: _t->addGeometry(); break;
        case 4: _t->removeGeometry(); break;
        case 5: _t->translateGeometries_x((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->translateGeometries_y((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->translateGeometries_z((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->scaleGeometries_x((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->scaleGeometries_y((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->scaleGeometries_z((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->rotateGeometries_x((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->rotateGeometries_y((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->rotateGeometries_z((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_actionAdd_Model_triggered(); break;
        case 15: _t->on_actionRemove_Selected_triggered(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
