#ifndef PASSWORDTYPE_H
#define PASSWORDTYPE_H
#include "customItem/abstractCustomItem.h"
class passwordType{
public:
    passwordType** subGroups;
    abstractCustomItem** items;
    bool isSubGroup;
    QString subGroupName;
};

#endif // PASSWORDTYPE_H
