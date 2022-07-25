#include "util/datapathgetter.h"
DataPathGetter::DataPathGetter(){
    portraitDir="portrait/";
    dataDir="data/";
    logsDir="logs/";
    accountsDataBasePath="data/accounts.pmd";
}
DataPathGetter& DataPathGetter::getInstance(){
    if(!instance)
        instance=new DataPathGetter();
    return *instance;
}
void DataPathGetter::deleteInstance(){
    delete instance;
}
QString DataPathGetter::getPortraitDir()
{
    return portraitDir;
}

QString DataPathGetter::getDataDir()
{
    return dataDir;
}
QString DataPathGetter::getLogsDir()
{
    return logsDir;
}
QString DataPathGetter::getAccountsDataBasePath()
{
    return accountsDataBasePath;
}

QString DataPathGetter::getCurrentAccountDataBasePath()
{
    return currentAccountDataBasePath;
}
