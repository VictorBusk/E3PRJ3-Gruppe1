/****************************************************************************
** Meta object code from reading C++ file 'e3pjr.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "e3pjr.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'e3pjr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_E3PJR[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x08,
      37,    6,    6,    6, 0x08,
      67,    6,    6,    6, 0x08,
      91,    6,    6,    6, 0x08,
     115,    6,    6,    6, 0x08,
     142,    6,    6,    6, 0x08,
     169,    6,    6,    6, 0x08,
     196,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_E3PJR[] = {
    "E3PJR\0\0on_pushCalibrateXYZ_pressed()\0"
    "on_pushCalibrateXYZ_clicked()\0"
    "on_pushSetXYZ_pressed()\0on_pushSetXYZ_clicked()\0"
    "on_pushGetXYZPos_pressed()\0"
    "on_pushGetXYZPos_clicked()\0"
    "on_pushGetXYZMax_pressed()\0"
    "on_pushGetXYZMax_clicked()\0"
};

void E3PJR::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        E3PJR *_t = static_cast<E3PJR *>(_o);
        switch (_id) {
        case 0: _t->on_pushCalibrateXYZ_pressed(); break;
        case 1: _t->on_pushCalibrateXYZ_clicked(); break;
        case 2: _t->on_pushSetXYZ_pressed(); break;
        case 3: _t->on_pushSetXYZ_clicked(); break;
        case 4: _t->on_pushGetXYZPos_pressed(); break;
        case 5: _t->on_pushGetXYZPos_clicked(); break;
        case 6: _t->on_pushGetXYZMax_pressed(); break;
        case 7: _t->on_pushGetXYZMax_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData E3PJR::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject E3PJR::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_E3PJR,
      qt_meta_data_E3PJR, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &E3PJR::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *E3PJR::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *E3PJR::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_E3PJR))
        return static_cast<void*>(const_cast< E3PJR*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int E3PJR::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
