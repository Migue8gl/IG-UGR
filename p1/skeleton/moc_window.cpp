/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata__window_t {
    QByteArrayData data[9];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata__window_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata__window_t qt_meta_stringdata__window = {
    {
QT_MOC_LITERAL(0, 0, 7), // "_window"
QT_MOC_LITERAL(1, 8, 15), // "mode_point_slot"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 5), // "State"
QT_MOC_LITERAL(4, 31, 14), // "mode_line_slot"
QT_MOC_LITERAL(5, 46, 14), // "mode_fill_slot"
QT_MOC_LITERAL(6, 61, 15), // "mode_chess_slot"
QT_MOC_LITERAL(7, 77, 14), // "load_item_slot"
QT_MOC_LITERAL(8, 92, 4) // "Item"

    },
    "_window\0mode_point_slot\0\0State\0"
    "mode_line_slot\0mode_fill_slot\0"
    "mode_chess_slot\0load_item_slot\0Item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data__window[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x0a /* Public */,
       5,    1,   45,    2, 0x0a /* Public */,
       6,    1,   48,    2, 0x0a /* Public */,
       7,    1,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void _window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<_window *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mode_point_slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->mode_line_slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->mode_fill_slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->mode_chess_slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->load_item_slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject _window::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata__window.data,
    qt_meta_data__window,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *_window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata__window.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int _window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
