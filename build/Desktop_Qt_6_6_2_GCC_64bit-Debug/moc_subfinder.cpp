/****************************************************************************
** Meta object code from reading C++ file 'subfinder.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/subfinder/subfinder.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'subfinder.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSSubfinderENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSSubfinderENDCLASS = QtMocHelpers::stringData(
    "Subfinder",
    "onFindButtonClicked",
    "",
    "onClearButtonClicked",
    "executeCommand",
    "updateCommandDisplay",
    "onModeChanged",
    "index",
    "updateCommandOutput",
    "result",
    "showVerboseOutputAsTable",
    "output",
    "onCopyOutputClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSubfinderENDCLASS_t {
    uint offsetsAndSizes[26];
    char stringdata0[10];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[21];
    char stringdata4[15];
    char stringdata5[21];
    char stringdata6[14];
    char stringdata7[6];
    char stringdata8[20];
    char stringdata9[7];
    char stringdata10[25];
    char stringdata11[7];
    char stringdata12[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSubfinderENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSubfinderENDCLASS_t qt_meta_stringdata_CLASSSubfinderENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "Subfinder"
        QT_MOC_LITERAL(10, 19),  // "onFindButtonClicked"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 20),  // "onClearButtonClicked"
        QT_MOC_LITERAL(52, 14),  // "executeCommand"
        QT_MOC_LITERAL(67, 20),  // "updateCommandDisplay"
        QT_MOC_LITERAL(88, 13),  // "onModeChanged"
        QT_MOC_LITERAL(102, 5),  // "index"
        QT_MOC_LITERAL(108, 19),  // "updateCommandOutput"
        QT_MOC_LITERAL(128, 6),  // "result"
        QT_MOC_LITERAL(135, 24),  // "showVerboseOutputAsTable"
        QT_MOC_LITERAL(160, 6),  // "output"
        QT_MOC_LITERAL(167, 19)   // "onCopyOutputClicked"
    },
    "Subfinder",
    "onFindButtonClicked",
    "",
    "onClearButtonClicked",
    "executeCommand",
    "updateCommandDisplay",
    "onModeChanged",
    "index",
    "updateCommandOutput",
    "result",
    "showVerboseOutputAsTable",
    "output",
    "onCopyOutputClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSubfinderENDCLASS[] = {

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
       6,    1,   66,    2, 0x08,    5 /* Private */,
       8,    1,   69,    2, 0x08,    7 /* Private */,
      10,    1,   72,    2, 0x08,    9 /* Private */,
      12,    0,   75,    2, 0x08,   11 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Subfinder::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSSubfinderENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSubfinderENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSubfinderENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Subfinder, std::true_type>,
        // method 'onFindButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onClearButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'executeCommand'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateCommandDisplay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onModeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateCommandOutput'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'showVerboseOutputAsTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onCopyOutputClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Subfinder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Subfinder *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onFindButtonClicked(); break;
        case 1: _t->onClearButtonClicked(); break;
        case 2: _t->executeCommand(); break;
        case 3: _t->updateCommandDisplay(); break;
        case 4: _t->onModeChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->updateCommandOutput((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->showVerboseOutputAsTable((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->onCopyOutputClicked(); break;
        default: ;
        }
    }
}

const QMetaObject *Subfinder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Subfinder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSubfinderENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Subfinder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
