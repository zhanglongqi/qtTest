#ifndef APPLICATIONS_H
#define APPLICATIONS_H
#include <QtGui/QApplication>


/// \author loong
/// \date 15.Aug.2013
/// \brief try to make multi-window program
///
class Application:public QApplication
{
    Q_OBJECT
public:
    Application(int argc,char *argv[]);
    ~Application();
public:
    void creatWindow();
};
/// \attention never leave the semicolon ;
#endif // APPLICATIONS_H
