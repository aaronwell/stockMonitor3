/****************************************************************************
** Meta object code from reading C++ file 'stockModel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../stockModel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stockModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StockModel_t {
    QByteArrayData data[12];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StockModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StockModel_t qt_meta_stringdata_StockModel = {
    {
QT_MOC_LITERAL(0, 0, 10), // "StockModel"
QT_MOC_LITERAL(1, 11, 23), // "onStockDataBeginRefresh"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 20), // "onStockDataRefreshed"
QT_MOC_LITERAL(4, 57, 7), // "stateOf"
QT_MOC_LITERAL(5, 65, 3), // "row"
QT_MOC_LITERAL(6, 69, 8), // "addStock"
QT_MOC_LITERAL(7, 78, 4), // "code"
QT_MOC_LITERAL(8, 83, 6), // "remove"
QT_MOC_LITERAL(9, 90, 18), // "updateCurrentStock"
QT_MOC_LITERAL(10, 109, 9), // "saveState"
QT_MOC_LITERAL(11, 119, 14) // "updateInterval"

    },
    "StockModel\0onStockDataBeginRefresh\0\0"
    "onStockDataRefreshed\0stateOf\0row\0"
    "addStock\0code\0remove\0updateCurrentStock\0"
    "saveState\0updateInterval"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StockModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       1,   64, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x09 /* Protected */,
       3,    0,   50,    2, 0x09 /* Protected */,

 // methods: name, argc, parameters, tag, flags
       4,    1,   51,    2, 0x02 /* Public */,
       6,    1,   54,    2, 0x02 /* Public */,
       8,    1,   57,    2, 0x02 /* Public */,
       9,    1,   60,    2, 0x02 /* Public */,
      10,    0,   63,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Int, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

 // properties: name, type, flags
      11, QMetaType::Int, 0x00095103,

       0        // eod
};

void StockModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StockModel *_t = static_cast<StockModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onStockDataBeginRefresh(); break;
        case 1: _t->onStockDataRefreshed(); break;
        case 2: { int _r = _t->stateOf((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->addStock((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->remove((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updateCurrentStock((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->saveState(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        StockModel *_t = static_cast<StockModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->updateInterval(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        StockModel *_t = static_cast<StockModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setUpdateInterval(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject StockModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_StockModel.data,
      qt_meta_data_StockModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StockModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StockModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StockModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int StockModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
