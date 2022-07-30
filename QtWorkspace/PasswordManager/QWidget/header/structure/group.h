#ifndef GROUP_H
#define GROUP_H
#include "keyItem.h"
class Group{
private:
    int groupType;
    QString groupName;
    QString describe;
    QDateTime createTime;
    QDateTime lastEditTime;
    QList<KeyItem*> keyItemList;
public:
    Group(int groupType,QString groupName,QDateTime createTime,QDateTime lastEditTime,QString describe);
    //Getter与Setter
    int getGroupType() const;
    const QString &getGroupName() const;
    void setGroupName(const QString &newGroupName);
    const QString &getDescribe() const;
    void setDescribe(const QString &newDescribe);
    const QDateTime &getCreateTime() const;
    const QDateTime &getLastEditTime() const;
    void setLastEditTime();
    //辅助函数
    int count();
    void clear();
    //重载运算符
    Group* operator<<(KeyItem* newKeyItem);
    KeyItem* operator[](int index);
    //增删元素与返回索引
    KeyItem* at(int index);
    bool removeAt(int i);
    void append(KeyItem* newKeyItem);
};
#endif // GROUP_H
