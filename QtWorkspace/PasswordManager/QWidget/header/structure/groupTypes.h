#ifndef GROUPTYPES_H
#define GROUPTYPES_H
#include "groupType.h"
class GroupTypes{
private:
    QList<GroupType*> groupTypeList;
public:
    //辅助函数
    int count();
    bool has(const QString& groupTypeName);
    int index(const QString& groupTypeName);
    //重载运算符
    GroupType* operator[](int index);
    GroupTypes* operator<<(GroupType* newGroupType);
    //增删元素与返回索引
    GroupType* at(int index);
    void append(GroupType* newGroupType);
    bool removeOne(const QString& groupTypeName);
    bool remove(const QStringList& groupTypeNames);
    QStringList getGroupTypeNames();
};
#endif // GROUPTYPES_H
