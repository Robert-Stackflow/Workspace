#include "structure/groups.h"
#pragma warning (disable:4100)
Groups::Groups(){
}
//辅助函数
int Groups::count(){
    return groupList.count();
}
void Groups::clear(){
    groupList.clear();
}
int Groups::index(const QString &groupName){
    for(int i=0;i<count();i++)
        if(groupList[i]->getGroupName()==groupName)
            return i;
    return -1;
}
bool Groups::has(const QString &groupName){
    if(index(groupName)==-1)
        return false;
    else
        return true;
}
Groups* Groups::operator<<(Group* newGroup){
    groupList<<newGroup;
    return this;
}
Group* Groups::operator[](int index){
    return groupList[index];
}
Group* Groups::at(int index){
    return groupList[index];
}
bool Groups::removeOne(const QString &groupName){
    int i=index(groupName);
    if(i==-1){
        return false;
    }
    else{
        groupList.removeAt(i);
        return true;
    }
}
bool Groups::removeAt(int i){
    if(i<0||i>=count()){
        return false;
    }
    else{
        groupList.removeAt(i);
        return true;
    }
}
bool Groups::remove(const QStringList &groupNames){
    bool flag=true;
    for(int i=0;i<count();i++)
        if(!removeOne(groupNames[i]))
            flag=false;
    return flag;
}
void Groups::append(Group* newGroup){
    groupList<<newGroup;
}
QStringList Groups::getGroupNames(){
    QStringList list;
    for(int i=0;i<count();i++)
        list<<groupList[i]->getGroupName();
    return list;
}
