#include "util/datapathgetter.h"
#include "util/shareddata.h"
DataPathGetter* DataPathGetter::sinstance=nullptr;
QString DataPathGetter::portraitDir="portrait/";
QString DataPathGetter::dataDir="data/";
QString DataPathGetter::logsDir="logs/";
QString DataPathGetter::defaultPortraitPath=":custom/icons/defaultPortrait.png";
DataPathGetter::DataPathGetter(){
}
DataPathGetter& DataPathGetter::instance(){
    if(!sinstance)
        sinstance=new DataPathGetter();
    return *sinstance;
}
void DataPathGetter::deleteInstance(){
    delete sinstance;
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
    return dataDir+"accounts.pmd";
}

QString DataPathGetter::getCurrentAccountDataBasePath()
{
    SharedData& sharedData = SharedData::instace();
    return dataDir+QString::number(sharedData.accountList.getActiveAccount()->getCreateTime().toTime_t())+".pmd";
}
QString DataPathGetter::getDefaultPortraitPath()
{
    return defaultPortraitPath;
}
