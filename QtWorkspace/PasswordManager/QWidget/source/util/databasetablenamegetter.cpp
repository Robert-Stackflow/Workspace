#include "util/databasetablenamegetter.h"
DataBaseTableNameGetter* DataBaseTableNameGetter::sinstance=nullptr;
QString DataBaseTableNameGetter::accountsTableName="accounts";
QString DataBaseTableNameGetter::groupsTableName="groups";
QString DataBaseTableNameGetter::groupTypesTableName="groupTypes";
QString DataBaseTableNameGetter::autofillInfoTableName="autofillInfo";
QString DataBaseTableNameGetter::groupTableNamePrefix="group_";
QString DataBaseTableNameGetter::groupTypeTableNamePrefix="groupType_";
DataBaseTableNameGetter::DataBaseTableNameGetter(){
}
DataBaseTableNameGetter& DataBaseTableNameGetter::instace(){
    if (!sinstance)
        sinstance = new DataBaseTableNameGetter();
    return *sinstance;
}
void DataBaseTableNameGetter::deleteInstace(){
    delete sinstance;
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
