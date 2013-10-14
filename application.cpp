#include <application.h>
#include <mainwindow.h>
 #include <QTimer>
#include <myQWi.h>
#include <test.h>
#include <statesMachine.cpp>
Application::Application(int argc,char *argv[]):QApplication(argc,argv)
{
  this->creatWindow();
 //  QTimer::singleShot(1000, this, SLOT(quit()));
}
Application::~Application()
{


}

void Application::creatWindow()
{
  //test0();
  test *tt = new test();
  tt->show ();
  //  myQWi *ww=new myQWi();
  //  ww->setWindowFlags(Qt::Window);
  //  ww->show ();
  //QWidget can't used for seprate window directly.

  /*
      enum WindowType
            Widget = 0x00000000,
            Window = 0x00000001,
            Dialog = 0x00000002 | Window,
            Sheet = 0x00000004 | Window,
            Drawer = 0x00000006 | Window,
            Popup = 0x00000008 | Window,
            Tool = 0x0000000a | Window,
            ToolTip = 0x0000000c | Window,
            SplashScreen = 0x0000000e | Window,
            Desktop = 0x00000010 | Window,
            SubWindow =  0x00000012,
    */

  //   QMainWindow *mm=new QMainWindow();
  //    mm->setCentralWidget(ww);
  //    mm->show();
  //    mm->showMaximized();
  //    MainWindow *mm2=new MainWindow();
  //    mm2->show();


}
