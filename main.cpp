#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QDebug>
#include <application.h>

int main(int argc, char *argv[])
{
    Application *app=new Application(argc,argv);
    return  app->exec();;
}
