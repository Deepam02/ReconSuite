/****************************************************************************
** Meta object code from reading C++ file 'dig.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../dig.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSdigENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSdigENDCLASS = QtMocHelpers::stringData(
    "dig",
    "setupUI",
    "",
    "setupConnections",
    "setLayoutAndTitle",
    "onClearButtonClicked",
    "executeCommand",
    "updateCommandOutput",
    "result",
    "onModeChanged",
    "index",
    "updateCommandDisplay"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSdigENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[4];
    char stringdata1[8];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[18];
    char stringdata5[21];
    char stringdata6[15];
    char stringdata7[20];
    char stringdata8[7];
    char stringdata9[14];
    char stringdata10[6];
    char stringdata11[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSdigENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSdigENDCLASS_t qt_meta_stringdata_CLASSdigENDCLASS = {
    {
        QT_MOC_LITERAL(0, 3),  // "dig"
        QT_MOC_LITERAL(4, 7),  // "setupUI"
        QT_MOC_LITERAL(12, 0),  // ""
        QT_MOC_LITERAL(13, 16),  // "setupConnections"
        QT_MOC_LITERAL(30, 17),  // "setLayoutAndTitle"
        QT_MOC_LITERAL(48, 20),  // "onClearButtonClicked"
        QT_MOC_LITERAL(69, 14),  // "executeCommand"
        QT_MOC_LITERAL(84, 19),  // "updateCommandOutput"
        QT_MOC_LITERAL(104, 6),  // "result"
        QT_MOC_LITERAL(111, 13),  // "onModeChanged"
        QT_MOC_LITERAL(125, 5),  // "index"
        QT_MOC_LITERAL(131, 20)   // "updateCommandDisplay"
    },
    "dig",
    "setupUI",
    "",
    "setupConnections",
    "setLayoutAndTitle",
    "onClearButtonClicked",
    "executeCommand",
    "updateCommandOutput",
    "result",
    "onModeChanged",
    "index",
    "updateCommandDisplay"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSdigENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x08,    1 /* Private */,
       3,    0,   63,    2, 0x08,    2 /* Private */,
       4,    0,   64,    2, 0x08,    3 /* Private */,
       5,    0,   65,    2, 0x08,    4 /* Private */,
       6,    0,   66,    2, 0x08,    5 /* Private */,
       7,    1,   67,    2, 0x08,    6 /* Private */,
       9,    1,   70,    2, 0x08,    8 /* Private */,
      11,    0,   73,    2, 0x08,   10 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject dig::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSdigENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSdigENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSdigENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<dig, std::true_type>,
        // method 'setupUI'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setupConnections'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setLayoutAndTitle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onClearButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'executeCommand'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateCommandOutput'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onModeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateCommandDisplay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void dig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<dig *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setupUI(); break;
        case 1: _t->setupConnections(); break;
        case 2: _t->setLayoutAndTitle(); break;
        case 3: _t->onClearButtonClicked(); break;
        case 4: _t->executeCommand(); break;
        case 5: _t->updateCommandOutput((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->onModeChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->updateCommandDisplay(); break;
        default: ;
        }
    }
}

const QMetaObject *dig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dig::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSdigENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int dig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
