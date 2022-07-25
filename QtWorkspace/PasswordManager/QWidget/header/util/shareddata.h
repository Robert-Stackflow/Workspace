#ifndef SHAREDDATA_H
#define SHAREDDATA_H
#include "structure/autofillInfo.h"
#include "structure/fieldTypes.h"
#include "structure/groupTypes.h"
#include "structure/groups.h"
#include "structure/account.h"
#include <QSqlDatabase>
class SharedData{
public:
    static SharedData* instance;
    static Account account;
    static Groups groupList;
    static GroupTypes groupTypeList;
    static FieldTypes fieldTypeList;
    static AutofillInfo autofillInfo;
    //数据库连接
    static QSqlDatabase database;
    SharedData();
public:
    static SharedData& getInstace();
    static void deleteInstace();
};
#endif // SHAREDDATA_H
