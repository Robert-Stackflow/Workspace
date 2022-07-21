/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../header/dialog/widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[23];
    char stringdata0[344];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 17), // "groupCountChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 8), // "saveSlot"
QT_MOC_LITERAL(4, 35, 17), // "saveMenuTriggered"
QT_MOC_LITERAL(5, 53, 12), // "newGroupSlot"
QT_MOC_LITERAL(6, 66, 15), // "deleteGroupSlot"
QT_MOC_LITERAL(7, 82, 13), // "editGroupSlot"
QT_MOC_LITERAL(8, 96, 9), // "changeTab"
QT_MOC_LITERAL(9, 106, 11), // "newItemSlot"
QT_MOC_LITERAL(10, 118, 12), // "moveItemSlot"
QT_MOC_LITERAL(11, 131, 12), // "copyItemSlot"
QT_MOC_LITERAL(12, 144, 14), // "removeItemSlot"
QT_MOC_LITERAL(13, 159, 15), // "openWebsiteSlot"
QT_MOC_LITERAL(14, 175, 16), // "copyItemInfoSlot"
QT_MOC_LITERAL(15, 192, 19), // "onGroupCountChanged"
QT_MOC_LITERAL(16, 212, 17), // "onTabIndexChanged"
QT_MOC_LITERAL(17, 230, 10), // "searchSlot"
QT_MOC_LITERAL(18, 241, 31), // "tableWidgetContextMenuRequested"
QT_MOC_LITERAL(19, 273, 3), // "pos"
QT_MOC_LITERAL(20, 277, 22), // "tableWidgetClickedSlot"
QT_MOC_LITERAL(21, 300, 19), // "optionButtonClicked"
QT_MOC_LITERAL(22, 320, 23) // "onGroupTypeCountChanged"

    },
    "Widget\0groupCountChanged\0\0saveSlot\0"
    "saveMenuTriggered\0newGroupSlot\0"
    "deleteGroupSlot\0editGroupSlot\0changeTab\0"
    "newItemSlot\0moveItemSlot\0copyItemSlot\0"
    "removeItemSlot\0openWebsiteSlot\0"
    "copyItemInfoSlot\0onGroupCountChanged\0"
    "onTabIndexChanged\0searchSlot\0"
    "tableWidgetContextMenuRequested\0pos\0"
    "tableWidgetClickedSlot\0optionButtonClicked\0"
    "onGroupTypeCountChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  115,    2, 0x08 /* Private */,
       4,    0,  116,    2, 0x08 /* Private */,
       5,    0,  117,    2, 0x08 /* Private */,
       6,    0,  118,    2, 0x08 /* Private */,
       7,    0,  119,    2, 0x08 /* Private */,
       8,    0,  120,    2, 0x08 /* Private */,
       9,    0,  121,    2, 0x08 /* Private */,
      10,    0,  122,    2, 0x08 /* Private */,
      11,    0,  123,    2, 0x08 /* Private */,
      12,    0,  124,    2, 0x08 /* Private */,
      13,    0,  125,    2, 0x08 /* Private */,
      14,    0,  126,    2, 0x08 /* Private */,
      15,    0,  127,    2, 0x08 /* Private */,
      16,    1,  128,    2, 0x08 /* Private */,
      17,    1,  131,    2, 0x08 /* Private */,
      18,    1,  134,    2, 0x08 /* Private */,
      20,    2,  137,    2, 0x08 /* Private */,
      21,    0,  142,    2, 0x08 /* Private */,
      22,    0,  143,    2, 0x08 /* Private */,

 // signals: parameters
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QPoint,   19,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->groupCountChanged(); break;
        case 1: _t->saveSlot(); break;
        case 2: _t->saveMenuTriggered(); break;
        case 3: _t->newGroupSlot(); break;
        case 4: _t->deleteGroupSlot(); break;
        case 5: _t->editGroupSlot(); break;
        case 6: _t->changeTab(); break;
        case 7: _t->newItemSlot(); break;
        case 8: _t->moveItemSlot(); break;
        case 9: _t->copyItemSlot(); break;
        case 10: _t->removeItemSlot(); break;
        case 11: _t->openWebsiteSlot(); break;
        case 12: _t->copyItemInfoSlot(); break;
        case 13: _t->onGroupCountChanged(); break;
        case 14: _t->onTabIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->searchSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->tableWidgetContextMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 17: _t->tableWidgetClickedSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 18: _t->optionButtonClicked(); break;
        case 19: _t->onGroupTypeCountChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::groupCountChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Widget.data,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void Widget::groupCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
