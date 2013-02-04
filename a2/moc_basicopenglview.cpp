/****************************************************************************
** Meta object code from reading C++ file 'basicopenglview.h'
**
** Created: Sun Feb 3 20:37:14 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "basicopenglview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'basicopenglview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BasicOpenGLView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   17,   16,   16, 0x05,
      62,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      91,   16,   16,   16, 0x0a,
     118,   16,   16,   16, 0x0a,
     145,   16,   16,   16, 0x0a,
     172,   16,   16,   16, 0x0a,
     195,   16,   16,   16, 0x0a,
     218,   16,   16,   16, 0x0a,
     241,   16,   16,   16, 0x0a,
     265,   16,   16,   16, 0x0a,
     289,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BasicOpenGLView[] = {
    "BasicOpenGLView\0\0m_GeometryName\0"
    "addedNewGeometry(std::string)\0"
    "removedGeometry(std::string)\0"
    "translateGeometries_x(int)\0"
    "translateGeometries_y(int)\0"
    "translateGeometries_z(int)\0"
    "scaleGeometries_x(int)\0scaleGeometries_y(int)\0"
    "scaleGeometries_z(int)\0rotateGeometries_x(int)\0"
    "rotateGeometries_y(int)\0rotateGeometries_z(int)\0"
};

void BasicOpenGLView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BasicOpenGLView *_t = static_cast<BasicOpenGLView *>(_o);
        switch (_id) {
        case 0: _t->addedNewGeometry((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 1: _t->removedGeometry((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 2: _t->translateGeometries_x((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->translateGeometries_y((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->translateGeometries_z((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->scaleGeometries_x((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->scaleGeometries_y((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->scaleGeometries_z((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->rotateGeometries_x((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->rotateGeometries_y((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->rotateGeometries_z((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BasicOpenGLView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BasicOpenGLView::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_BasicOpenGLView,
      qt_meta_data_BasicOpenGLView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BasicOpenGLView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BasicOpenGLView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BasicOpenGLView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BasicOpenGLView))
        return static_cast<void*>(const_cast< BasicOpenGLView*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int BasicOpenGLView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void BasicOpenGLView::addedNewGeometry(std::string _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BasicOpenGLView::removedGeometry(std::string _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
