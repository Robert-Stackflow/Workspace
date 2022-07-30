#ifndef KEYITEM_H
#define KEYITEM_H
#include <QString>
#include <QDateTime>
class KeyItem{
private:
    int groupType;
    QStringList fieldValueList;
    QDateTime createTime;
    QDateTime lastEditTime;
public:
    KeyItem(int groupType,QStringList fieldValueList);
    KeyItem(int groupType,QDateTime createTime,QDateTime lastEditTime,QStringList fieldValueList);
    int getGroupType() const;
    const QDateTime &getCreateTime() const;
    const QDateTime &getLastEditTime() const;
    void setLastEditTime();
    QString toString();
    //重载运算符
    QString operator[](int index);
    KeyItem operator<<(QString newFieldValue);
    //增删元素与返回索引
    QString at(int index);
    void append(QString newFieldValue);
};
#endif // KEYITEM_H
