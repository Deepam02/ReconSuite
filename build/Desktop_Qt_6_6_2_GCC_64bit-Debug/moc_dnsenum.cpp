/****************************************************************************
** Meta object code from reading C++ file 'dnsenum.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/dnsenum/dnsenum.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dnsenum.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSdnsenumENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSdnsenumENDCLASS = QtMocHelpers::stringData(
    "dnsenum",
    "setupUI",
    "",
    "setupConnections",
    "setLayoutAndTitle",
    "updateCommandDisplay",
    "executeCommand",
    "onClearButtonClicked",
    "updateCommandOutput",
    "result"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSdnsenumENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[8];
    char stringdata1[8];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[18];
    char stringdata5[21];
    char stringdata6[15];
    char stringdata7[21];
    char stringdata8[20];
    char stringdata9[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSdnsenumENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSdnsenumENDCLASS_t qt_meta_stringdata_CLASSdnsenumENDCLASS = {
    {
        QT_MOC_LITERAL(0, 7),  // "dnsenum"
        QT_MOC_LITERAL(8, 7),  // "setupUI"
        QT_MOC_LITERAL(16, 0),  // ""
        QT_MOC_LITERAL(17, 16),  // "setupConnections"
        QT_MOC_LITERAL(34, 17),  // "setLayoutAndTitle"
        QT_MOC_LITERAL(52, 20),  // "updateCommandDisplay"
        QT_MOC_LITERAL(73, 14),  // "executeCommand"
        QT_MOC_LITERAL(88, 20),  // "onClearButtonClicked"
        QT_MOC_LITERAL(109, 19),  // "updateCommandOutput"
        QT_MOC_LITERAL(129, 6)   // "result"
    },
    "dnsenum",
    "setupUI",
    "",
    "setupConnections",
    "setLayoutAndTitle",
    "updateCommandDisplay",
    "executeCommand",
    "onClearButtonClicked",
    "updateCommandOutput",
    "result"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSdnsenumENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x08,    1 /* Private */,
       3,    0,   57,    2, 0x08,    2 /* Private */,
       4,    0,   58,    2, 0x08,    3 /* Private */,
       5,    0,   59,    2, 0x08,    4 /* Private */,
       6,    0,   60,    2, 0x08,    5 /* Private */,
       7,    0,   61,    2, 0x08,    6 /* Private */,
       8,    1,   62,    2, 0x08,    7 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

Q_CONSTINIT const QMetaObject dnsenum::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSdnsenumENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSdnsenumENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSdnsenumENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<dnsenum, std::true_type>,
        // method 'setupUI'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setupConnections'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setLayoutAndTitle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateCommandDisplay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'executeCommand'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onClearButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateCommandOutput'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void dnsenum::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<dnsenum *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setupUI(); break;
        case 1: _t->setupConnections(); break;
        case 2: _t->setLayoutAndTitle(); break;
        case 3: _t->updateCommandDisplay(); break;
        case 4: _t->executeCommand(); break;
        case 5: _t->onClearButtonClicked(); break;
        case 6: _t->updateCommandOutput((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *dnsenum::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dnsenum::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSdnsenumENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int dnsenum::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
