#include "structure/account.h"
Account::Account(){

}
Account::Account(const QString &newUsername,const QString &newPassword,const QString &newPortraitPath)
{
    this->username=newUsername;
    this->password=newPassword;
    this->portraitPath=newPortraitPath;
}

const QString &Account::getUsername() const
{
    return username;
}

void Account::setUsername(const QString &newUsername)
{
    username = newUsername;
}

const QString &Account::getPassword() const
{
    return password;
}

void Account::setPassword(const QString &newPassword)
{
    password = newPassword;
}

const QDateTime &Account::getCreateTime() const
{
    return createTime;
}

const QDateTime &Account::getLastEditTime() const
{
    return lastEditTime;
}

void Account::setLastEditTime()
{
    lastEditTime = QDateTime::currentDateTime();
}

const QString &Account::getPortraitPath() const
{
    return portraitPath;
}

void Account::setPortraitPath(const QString &newPortraitPath)
{
    portraitPath = newPortraitPath;
}
