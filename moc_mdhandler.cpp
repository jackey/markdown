/****************************************************************************
** Meta object code from reading C++ file 'mdhandler.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mdhandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mdhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MdHandler[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MdHandler[] = {
    "MdHandler\0\0html\0mdCompiled(QString)\0"
    "handleMdChanged()\0"
};

void MdHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MdHandler *_t = static_cast<MdHandler *>(_o);
        switch (_id) {
        case 0: _t->mdCompiled((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->handleMdChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MdHandler::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MdHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MdHandler,
      qt_meta_data_MdHandler, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MdHandler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MdHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MdHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MdHandler))
        return static_cast<void*>(const_cast< MdHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int MdHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void MdHandler::mdCompiled(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
