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
    GroupType(QString groupTypeName,QString describe,QList<AbstractCustomField*> customFieldList);
    GroupType(QString groupTypeName,QDateTime createTime,QDateTime lastEditTime,QString describe);
    //成员的setter与getter
    const QString &getDescribe() const;
    void setDescribe(const QString &newDescribe);
    const QDateTime &getCreateTime() const;
    const QDateTime &getLastEditTime() const;
    void setLastEditTime();
    const QString &getGroupTypeName() const;
    void setGroupTypeName(const QString &newGroupTypeName);
    void setCustomFieldList(const QList<AbstractCustomField *> &newCustomFieldList);
    //辅助函数
    int count();
    void clear();
    int index(const QString &name);
    bool has(const QString &name);
    GroupType* clone();
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
    QString getCreateSql(const QString& tableName);
    QString getUpdateSql(const QString &tableName);
    QString getInsertSql(const QString &tableName);
};
#endif // GROUPTYPE_H
