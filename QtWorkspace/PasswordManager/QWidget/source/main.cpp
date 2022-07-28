#include "dialog/logindialog.h"
#include "ui_logindialog.h"
#include "QsLog.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //初始化Logger
    QsLogging::Logger& logger=QsLogging::Logger::getFileLogger("PUBLIC","PROGRAM");
    logger.setProgramName("Password Manager");
    logger.setLoggingLevel(QsLogging::TraceLevel);
    logger.setDefaultLogPath("logs/log.txt");
    QLOG_INFO()<<"Running Password Manager...";
    loginDialog login;
    login.show();
    return a.exec();
}
