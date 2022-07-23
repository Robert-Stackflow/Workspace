#ifndef GROUPTYPE_H
#define GROUPTYPE_H
#include <QDateTime>
#include "customField/abstractCustomField.h"
class GroupType{
private:
    QString groupTypeName;
    QString describe;
    QDateTime createTime;
    QDateTime lastEditTime;
    QList<AbstractCustomField*> customFieldList;
public:
    //构造函数
    GroupType(QString groupTypeName,QString describe,QList<AbstractCustomField*> items);
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
    GroupType* operator<<(AbstractCustomField* newField);
    AbstractCustomField* operator[](int index);
    //增删元素与返回索引
    AbstractCustomField* at(int index);
    bool removeAt(int index);
    bool removeOne(const QString &name);
    bool remove(const QStringList &names);
    void append(AbstractCustomField* newField);
    QStringList getFieldNames();
};
#endif // GROUPTYPE_H
