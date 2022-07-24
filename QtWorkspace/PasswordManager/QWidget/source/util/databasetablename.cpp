#include "util/databasetablename.h"

const QString &dataBaseTableName::getAccountTableName() const
{
    return accountTableName;
}

dataBaseTableName::dataBaseTableName(){
    accountTableName="accounts";
    groupsTableName="groups";
    groupTypesTableName="groupTypes";
    autofillInfoTableName="autofillInfo";
    groupTableNamePrefix="group_";
    groupTypeTableNamePrefix="groupType_";
}
QString dataBaseTableName::getGroupsTableName(){
    return groupsTableName;
}
QString dataBaseTableName::getGroupTypesTableName(){
    return groupTypesTableName;
}
QString dataBaseTableName::getAutofillInfoTableName(){
    return autofillInfoTableName;
}
QString dataBaseTableName::getGroupTableName(QString groupName){
    return groupTableNamePrefix+groupName;
}
QString dataBaseTableName::getGroupTypeTableName(QString groupTypeName){
    return groupTypeTableNamePrefix+groupTypeName;
}
