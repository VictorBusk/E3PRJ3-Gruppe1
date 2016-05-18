/****************************************************************************
** Meta object code from reading C++ file 'spitestprogram.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "spitestprogram.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spitestprogram.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SpiTestProgram[] = {

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
      16,   15,   15,   15, 0x08,
      37,   15,   15,   15, 0x08,
      59,   15,   15,   15, 0x08,
      82,   15,   15,   15, 0x08,
     106,   15,   15,   15, 0x08,
     128,   15,   15,   15, 0x08,
     151,   15,   15,   15, 0x08,
     175,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SpiTestProgram[] = {
    "SpiTestProgram\0\0on_pbRedOn_clicked()\0"
    "on_pbRedOff_clicked()\0on_pbGreenOn_clicked()\0"
    "on_pbGreenOff_clicked()\0on_pbBlueOn_clicked()\0"
    "on_pbBlueOff_clicked()\0on_pbReslutat_clicked()\0"
    "on_pbClear_clicked()\0"
};

void SpiTestProgram::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SpiTestProgram *_t = static_cast<SpiTestProgram *>(_o);
        switch (_id) {
        case 0: _t->on_pbRedOn_clicked(); break;
        case 1: _t->on_pbRedOff_clicked(); break;
        case 2: _t->on_pbGreenOn_clicked(); break;
        case 3: _t->on_pbGreenOff_clicked(); break;
        case 4: _t->on_pbBlueOn_clicked(); break;
        case 5: _t->on_pbBlueOff_clicked(); break;
        case 6: _t->on_pbReslutat_clicked(); break;
        case 7: _t->on_pbClear_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SpiTestProgram::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SpiTestProgram::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SpiTestProgram,
      qt_meta_data_SpiTestProgram, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SpiTestProgram::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SpiTestProgram::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SpiTestProgram::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SpiTestProgram))
        return static_cast<void*>(const_cast< SpiTestProgram*>(this));
    return QWidget::qt_metacast(_clname);
}

int SpiTestProgram::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
