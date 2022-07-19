#ifndef GROUPTYPE_H
#define GROUPTYPE_H
#include <QDateTime>
#include "customItem/abstractCustomItem.h"
class groupType{
protected:
    int itemCount;
    QString describe;
    QDateTime createTime;
    QDateTime lastEditTime;
    QString groupTypeName;
    QList<abstractCustomItem*> items;
private:
    static int groupTypesCount;
};

#endif // GROUPTYPE_H
