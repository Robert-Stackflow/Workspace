#ifndef KEYITEM_H
#define KEYITEM_H
#include <QString>
#include <QDateTime>
class KeyItem{
private:
    int flag=0;
    int groupType;
    QStringList fieldNameList;
    QStringList fieldValueList;
    QDateTime createTime;
    QDateTime lastEditTime;
public:
    KeyItem(int groupType,QDateTime createTime,QDateTime lastEditTime,QStringList fieldNameList);
    int getFlag() const;
    void setFlag(int newFlag);
    int getGroupType() const;
    const QDateTime &getCreateTime() const;
    const QDateTime &getLastEditTime() const;
    void setLastEditTime();
    QString toString();
};
#endif // KEYITEM_H
