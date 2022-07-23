/****************************************************************************
** Meta object code from reading C++ file 'abstractCustomField.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../header/customField/abstractCustomField.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abstractCustomField.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AbstractCustomField_t {
    QByteArrayData data[14];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AbstractCustomField_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AbstractCustomField_t qt_meta_stringdata_AbstractCustomField = {
    {
QT_MOC_LITERAL(0, 0, 19), // "AbstractCustomField"
QT_MOC_LITERAL(1, 20, 17), // "isRequiredChoices"
QT_MOC_LITERAL(2, 38, 8), // "OPTIONAL"
QT_MOC_LITERAL(3, 47, 8), // "REQUIRED"
QT_MOC_LITERAL(4, 56, 21), // "controllerTypeChoices"
QT_MOC_LITERAL(5, 78, 8), // "LINEEDIT"
QT_MOC_LITERAL(6, 87, 8), // "COMBOBOX"
QT_MOC_LITERAL(7, 96, 8), // "TEXTEDIT"
QT_MOC_LITERAL(8, 105, 15), // "dataTypeChoices"
QT_MOC_LITERAL(9, 121, 6), // "NORMAL"
QT_MOC_LITERAL(10, 128, 8), // "PASSWORD"
QT_MOC_LITERAL(11, 137, 4), // "MAIL"
QT_MOC_LITERAL(12, 142, 6), // "MOBILE"
QT_MOC_LITERAL(13, 149, 7) // "WEBSITE"

    },
    "AbstractCustomField\0isRequiredChoices\0"
    "OPTIONAL\0REQUIRED\0controllerTypeChoices\0"
    "LINEEDIT\0COMBOBOX\0TEXTEDIT\0dataTypeChoices\0"
    "NORMAL\0PASSWORD\0MAIL\0MOBILE\0WEBSITE"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AbstractCustomField[] = {

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
       4,    4, 0x0,    3,   33,
       8,    8, 0x0,    5,   39,

 // enum data: key, value
       2, uint(AbstractCustomField::OPTIONAL),
       3, uint(AbstractCustomField::REQUIRED),
       5, uint(AbstractCustomField::LINEEDIT),
       6, uint(AbstractCustomField::COMBOBOX),
       7, uint(AbstractCustomField::TEXTEDIT),
       9, uint(AbstractCustomField::NORMAL),
      10, uint(AbstractCustomField::PASSWORD),
      11, uint(AbstractCustomField::MAIL),
      12, uint(AbstractCustomField::MOBILE),
      13, uint(AbstractCustomField::WEBSITE),

       0        // eod
};

void AbstractCustomField::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject AbstractCustomField::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_AbstractCustomField.data,
    qt_meta_data_AbstractCustomField,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AbstractCustomField::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AbstractCustomField::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AbstractCustomField.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AbstractCustomField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
