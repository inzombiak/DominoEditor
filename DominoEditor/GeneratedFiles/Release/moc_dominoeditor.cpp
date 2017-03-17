/****************************************************************************
** Meta object code from reading C++ file 'dominoeditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../dominoeditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dominoeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DominoEditor_t {
    QByteArrayData data[17];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DominoEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DominoEditor_t qt_meta_stringdata_DominoEditor = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DominoEditor"
QT_MOC_LITERAL(1, 13, 15), // "ShowForceEditor"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 24), // "ForceSpinBoxValueChanged"
QT_MOC_LITERAL(4, 55, 5), // "value"
QT_MOC_LITERAL(5, 61, 23), // "ShowBulletObjectCreator"
QT_MOC_LITERAL(6, 85, 27), // "BulletObjectSettingsChanged"
QT_MOC_LITERAL(7, 113, 15), // "PhysicsSettings"
QT_MOC_LITERAL(8, 129, 8), // "settings"
QT_MOC_LITERAL(9, 138, 23), // "ShowDominoPatternEditor"
QT_MOC_LITERAL(10, 162, 15), // "GenerateObjects"
QT_MOC_LITERAL(11, 178, 28), // "std::vector<DominoTransform>"
QT_MOC_LITERAL(12, 207, 10), // "transforms"
QT_MOC_LITERAL(13, 218, 10), // "numColumns"
QT_MOC_LITERAL(14, 229, 7), // "numRows"
QT_MOC_LITERAL(15, 237, 8), // "xSpacing"
QT_MOC_LITERAL(16, 246, 8) // "zSpacing"

    },
    "DominoEditor\0ShowForceEditor\0\0"
    "ForceSpinBoxValueChanged\0value\0"
    "ShowBulletObjectCreator\0"
    "BulletObjectSettingsChanged\0PhysicsSettings\0"
    "settings\0ShowDominoPatternEditor\0"
    "GenerateObjects\0std::vector<DominoTransform>\0"
    "transforms\0numColumns\0numRows\0xSpacing\0"
    "zSpacing"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DominoEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    1,   45,    2, 0x0a /* Public */,
       5,    0,   48,    2, 0x0a /* Public */,
       6,    1,   49,    2, 0x0a /* Public */,
       9,    0,   52,    2, 0x0a /* Public */,
      10,    5,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::Double,   12,   13,   14,   15,   16,

       0        // eod
};

void DominoEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DominoEditor *_t = static_cast<DominoEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ShowForceEditor(); break;
        case 1: _t->ForceSpinBoxValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->ShowBulletObjectCreator(); break;
        case 3: _t->BulletObjectSettingsChanged((*reinterpret_cast< PhysicsSettings(*)>(_a[1]))); break;
        case 4: _t->ShowDominoPatternEditor(); break;
        case 5: _t->GenerateObjects((*reinterpret_cast< std::vector<DominoTransform>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        default: ;
        }
    }
}

const QMetaObject DominoEditor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_DominoEditor.data,
      qt_meta_data_DominoEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DominoEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DominoEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DominoEditor.stringdata0))
        return static_cast<void*>(const_cast< DominoEditor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int DominoEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
