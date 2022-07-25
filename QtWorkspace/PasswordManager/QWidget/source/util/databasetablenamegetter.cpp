#include "util/databasetablenamegetter.h"
DataBaseTableNameGetter::DataBaseTableNameGetter(){
    accountsTableName="accounts";
    groupsTableName="groups";
    groupTypesTableName="groupTypes";
    autofillInfoTableName="autofillInfo";
    groupTableNamePrefix="group_";
    groupTypeTableNamePrefix="groupType_";
}
DataBaseTableNameGetter& DataBaseTableNameGetter::getInstace(){
    if (!instance)
        instance = new DataBaseTableNameGetter();
    return *instance;
}
void DataBaseTableNameGetter::deleteInstace(){
    delete instance;
}
QString DataBaseTableNameGetter::getAccountsTableName(){
    return accountsTableName;
}
QString DataBaseTableNameGetter::getGroupsTableName(){
    return groupsTableName;
}
QString DataBaseTableNameGetter::getGroupTypesTableName(){
    return groupTypesTableName;
}
QString DataBaseTableNameGetter::getAutofillInfoTableName(){
    return autofillInfoTableName;
}
QString DataBaseTableNameGetter::getGroupTableName(QString groupName){
    return groupTableNamePrefix+groupName;
}
QString DataBaseTableNameGetter::getGroupTypeTableName(QString groupTypeName){
    return groupTypeTableNamePrefix+groupTypeName;
}
