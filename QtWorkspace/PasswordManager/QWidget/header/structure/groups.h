#ifndef GROUPS_H
#define GROUPS_H
#include "group.h"
class Groups{
private:
    QList<Group*> groupList;
public:
    Groups();
    //辅助函数
    int count();
    void clear();
    int index(const QString &groupName);
    bool has(const QString &groupName);
    //重载运算符
    Groups* operator<<(Group* newGroup);
    Group* operator[](int index);
    //增删元素与返回索引
    Group* at(int index);
    bool removeAt(int i);
    bool removeOne(const QString &groupName);
    bool remove(const QStringList &groupNames);
    void append(Group* newGroup);
    QStringList getGroupNames();
};
#endif // GROUPS_H
