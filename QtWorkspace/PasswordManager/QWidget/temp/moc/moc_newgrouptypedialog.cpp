/****************************************************************************
** Meta object code from reading C++ file 'newgrouptypedialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../header/dialog/newgrouptypedialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newgrouptypedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_newGroupTypeDialog_t {
    QByteArrayData data[13];
    char stringdata0[256];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_newGroupTypeDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_newGroupTypeDialog_t qt_meta_stringdata_newGroupTypeDialog = {
    {
QT_MOC_LITERAL(0, 0, 18), // "newGroupTypeDialog"
QT_MOC_LITERAL(1, 19, 21), // "groupTypeCountChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 29), // "typeManagerTableWidgetClicked"
QT_MOC_LITERAL(4, 72, 31), // "onTypeManagerTableWidgetClicked"
QT_MOC_LITERAL(5, 104, 17), // "onEditTypeClicked"
QT_MOC_LITERAL(6, 122, 19), // "onDeleteTypeClicked"
QT_MOC_LITERAL(7, 142, 17), // "onCopyTypeClicked"
QT_MOC_LITERAL(8, 160, 16), // "onNewTypeClicked"
QT_MOC_LITERAL(9, 177, 15), // "onCancelClicked"
QT_MOC_LITERAL(10, 193, 16), // "onConfirmClicked"
QT_MOC_LITERAL(11, 210, 17), // "onAddFieldClicked"
QT_MOC_LITERAL(12, 228, 27) // "onIsReqiuredCheckBoxToggled"

    },
    "newGroupTypeDialog\0groupTypeCountChanged\0"
    "\0typeManagerTableWidgetClicked\0"
    "onTypeManagerTableWidgetClicked\0"
    "onEditTypeClicked\0onDeleteTypeClicked\0"
    "onCopyTypeClicked\0onNewTypeClicked\0"
    "onCancelClicked\0onConfirmClicked\0"
    "onAddFieldClicked\0onIsReqiuredCheckBoxToggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_newGroupTypeDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    1,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void newGroupTypeDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<newGroupTypeDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->groupTypeCountChanged(); break;
        case 1: _t->typeManagerTableWidgetClicked(); break;
        case 2: _t->onTypeManagerTableWidgetClicked(); break;
        case 3: _t->onEditTypeClicked(); break;
        case 4: _t->onDeleteTypeClicked(); break;
        case 5: _t->onCopyTypeClicked(); break;
        case 6: _t->onNewTypeClicked(); break;
        case 7: _t->onCancelClicked(); break;
        case 8: _t->onConfirmClicked(); break;
        case 9: _t->onAddFieldClicked(); break;
        case 10: _t->onIsReqiuredCheckBoxToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (newGroupTypeDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&newGroupTypeDialog::groupTypeCountChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (newGroupTypeDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&newGroupTypeDialog::typeManagerTableWidgetClicked)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject newGroupTypeDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_newGroupTypeDialog.data,
    qt_meta_data_newGroupTypeDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *newGroupTypeDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *newGroupTypeDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_newGroupTypeDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int newGroupTypeDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void newGroupTypeDialog::groupTypeCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void newGroupTypeDialog::typeManagerTableWidgetClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
