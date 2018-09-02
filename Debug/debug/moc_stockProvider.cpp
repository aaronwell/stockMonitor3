/****************************************************************************
** Meta object code from reading C++ file 'stockProvider.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../stockProvider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stockProvider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StockProvider_t {
    QByteArrayData data[10];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StockProvider_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StockProvider_t qt_meta_stringdata_StockProvider = {
    {
QT_MOC_LITERAL(0, 0, 13), // "StockProvider"
QT_MOC_LITERAL(1, 14, 12), // "beginRefresh"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 9), // "refreshed"
QT_MOC_LITERAL(4, 38, 6), // "remind"
QT_MOC_LITERAL(5, 45, 8), // "contents"
QT_MOC_LITERAL(6, 54, 17), // "onRefreshFinished"
QT_MOC_LITERAL(7, 72, 14), // "onRefreshError"
QT_MOC_LITERAL(8, 87, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(9, 115, 4) // "code"

    },
    "StockProvider\0beginRefresh\0\0refreshed\0"
    "remind\0contents\0onRefreshFinished\0"
    "onRefreshError\0QNetworkReply::NetworkError\0"
    "code"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StockProvider[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    1,   41,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   44,    2, 0x09 /* Protected */,
       7,    1,   45,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void StockProvider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StockProvider *_t = static_cast<StockProvider *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->beginRefresh(); break;
        case 1: _t->refreshed(); break;
        case 2: _t->remind((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->onRefreshFinished(); break;
        case 4: _t->onRefreshError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StockProvider::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StockProvider::beginRefresh)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (StockProvider::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StockProvider::refreshed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (StockProvider::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StockProvider::remind)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject StockProvider::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_StockProvider.data,
      qt_meta_data_StockProvider,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StockProvider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StockProvider::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StockProvider.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int StockProvider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void StockProvider::beginRefresh()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void StockProvider::refreshed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void StockProvider::remind(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
