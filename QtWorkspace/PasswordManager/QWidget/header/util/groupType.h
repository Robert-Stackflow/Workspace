#ifndef GROUPTYPE_H
#define GROUPTYPE_H
#include <QDateTime>
#include "customItem/abstractCustomItem.h"
class groupType{
private:
    QString describe;
    QDateTime createTime;
    QDateTime lastEditTime;
    QString groupTypeName;
    customItems* items;
public:
    //构造函数
    groupType(QString groupTypeName,QString describe,customItems* items);
    //成员的setter与getter
    const QString &getDescribe() const;
    void setDescribe(const QString &newDescribe);
    const QDateTime &getCreateTime() const;
    const QDateTime &getLastEditTime() const;
    void setLastEditTime();
    const QString &getGroupTypeName() const;
    void setGroupTypeName(const QString &newGroupTypeName);
    //辅助函数
    int count();
    void clear();
    int index(const QString &name);
    bool has(const QString &name);
    //重载运算符
    groupType* operator<<(abstractCustomItem* newItem);
    abstractCustomItem* operator[](int index);
    //增删元素与返回索引
    abstractCustomItem* at(int index);
    bool removeOne(const QString &name);
    bool remove(const QStringList &names);
    void append(abstractCustomItem* newItem);
    QStringList getItemNames();
};
class groupTypes:public QObject{
    Q_OBJECT
private:
    QList<groupType*> groupTypeList;
public:
    //辅助函数
    int count();
    bool has(const QString& groupTypeName);
    int index(const QString& groupTypeName);
    //重载运算符
    groupType* operator[](int index);
    groupTypes* operator<<(groupType* newGroupType);
    //增删元素与返回索引
    groupType* at(int index);
    void append(groupType* newGroupType);
    bool removeOne(const QString& groupTypeName);
    bool remove(const QStringList& groupTypeNames);
    QStringList getGroupTypeNames();
};

#endif // GROUPTYPE_H
