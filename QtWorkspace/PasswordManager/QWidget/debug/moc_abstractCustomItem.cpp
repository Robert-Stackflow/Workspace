/****************************************************************************
** Meta object code from reading C++ file 'abstractCustomItem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../header/customItem/abstractCustomItem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abstractCustomItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_abstractCustomItem_t {
    QByteArrayData data[16];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_abstractCustomItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_abstractCustomItem_t qt_meta_stringdata_abstractCustomItem = {
    {
QT_MOC_LITERAL(0, 0, 18), // "abstractCustomItem"
QT_MOC_LITERAL(1, 19, 17), // "isRequiredChoices"
QT_MOC_LITERAL(2, 37, 8), // "OPTIONAL"
QT_MOC_LITERAL(3, 46, 8), // "REQUIRED"
QT_MOC_LITERAL(4, 55, 21), // "controllerTypeChoices"
QT_MOC_LITERAL(5, 77, 8), // "LINEEDIT"
QT_MOC_LITERAL(6, 86, 8), // "COMBOBOX"
QT_MOC_LITERAL(7, 95, 8), // "CHECKBOX"
QT_MOC_LITERAL(8, 104, 5), // "RADIO"
QT_MOC_LITERAL(9, 110, 8), // "TEXTEDIT"
QT_MOC_LITERAL(10, 119, 15), // "dataTypeChoices"
QT_MOC_LITERAL(11, 135, 6), // "NORMAL"
QT_MOC_LITERAL(12, 142, 8), // "PASSWORD"
QT_MOC_LITERAL(13, 151, 4), // "MAIL"
QT_MOC_LITERAL(14, 156, 6), // "MOBILE"
QT_MOC_LITERAL(15, 163, 7) // "WEBSITE"

    },
    "abstractCustomItem\0isRequiredChoices\0"
    "OPTIONAL\0REQUIRED\0controllerTypeChoices\0"
    "LINEEDIT\0COMBOBOX\0CHECKBOX\0RADIO\0"
    "TEXTEDIT\0dataTypeChoices\0NORMAL\0"
    "PASSWORD\0MAIL\0MOBILE\0WEBSITE"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_abstractCustomItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       3,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    2,   29,
       4,    4, 0x0,    5,   33,
      10,   10, 0x0,    5,   43,

 // enum data: key, value
       2, uint(abstractCustomItem::OPTIONAL),
       3, uint(abstractCustomItem::REQUIRED),
       5, uint(abstractCustomItem::LINEEDIT),
       6, uint(abstractCustomItem::COMBOBOX),
       7, uint(abstractCustomItem::CHECKBOX),
       8, uint(abstractCustomItem::RADIO),
       9, uint(abstractCustomItem::TEXTEDIT),
      11, uint(abstractCustomItem::NORMAL),
      12, uint(abstractCustomItem::PASSWORD),
      13, uint(abstractCustomItem::MAIL),
      14, uint(abstractCustomItem::MOBILE),
      15, uint(abstractCustomItem::WEBSITE),

       0        // eod
};

void abstractCustomItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject abstractCustomItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_abstractCustomItem.data,
    qt_meta_data_abstractCustomItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *abstractCustomItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *abstractCustomItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_abstractCustomItem.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int abstractCustomItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
