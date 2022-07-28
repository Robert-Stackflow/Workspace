#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QString>
#include <QDateTime>

class Account
{
private:
    QString username;
    QString password;
    QDateTime createTime;
    QDateTime lastEditTime;
    QString portraitPath;
public:
    Account();
    Account(const QString &newUsername,const QString &newPassword,const QString &newPortraitPath="");
    Account(const QString &newUsername,QDateTime newCreateTime,QDateTime newLastEditTime,const QString &newPortraitPath);
    const QString &getUsername() const;
    void setUsername(const QString &newUsername);
    const QString &getPassword() const;
    void setPassword(const QString &newPassword);
    const QDateTime &getCreateTime() const;
    const QDateTime &getLastEditTime() const;
    void setLastEditTime();
    const QString &getPortraitPath() const;
    void setPortraitPath(const QString &newPortraitPath);
    QString toString();
};

#endif // ACCOUNT_H
