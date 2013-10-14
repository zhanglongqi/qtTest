#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPushButton>
#include <QTextCodec>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QStringList>
#include <QColorDialog>
#include <QLabel>
#include <QMouseEvent>
#include <QMessageBox>
#include <fstream>
#include <iostream>
#include <QString>
#include <string>
#include <stdlib.h>
#include <QFile>
#include <QSystemTrayIcon>
#include <myQWi.h>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{

  ui->setupUi(this);

  /// \note 用QMainWindow创建的窗口会自动在中间放置一个QWidget从而使其本身无法获得鼠标事件。
  ///         本例中用一个自定义的QWidget替换掉那个自动填充的从而可以获得各种鼠标事件
  ///
  cenQWi=new myQWi();
  MainWindow::setCentralWidget(cenQWi);

  ///将窗口显示居中
  ///
 // resize (800,600);
 // this->centerWidget(this,true);
this->showMaximized ();

  initMenu();
  fileRWTest();
  setSystemIcon();
}
/// @brief Destructor
///
MainWindow::~MainWindow()
{
  delete ui;
}

/// \brief for file Write Read test
///
void  MainWindow::fileRWTest(){
  //

  std::cout << "2. Some normal iostream output before using qDebug\n";
  qDebug()<<"begin...";

  QFile file0("file.dat");
  file0.open(QIODevice::WriteOnly);
  QDataStream out(&file0);   // we will serialize the data into the file
  //   out.setVersion( QDataStream::Qt_4_2 );
  out << QString("the answer isV2.12Beta");   // serialize a string
  out << (qint32)42;        // serialize an integer
  file0.close();

  QFile file2("file.dat");
  file2.open(QIODevice::ReadOnly);
  QDataStream in(&file2);    // read the data serialized from the file
  //   in.setVersion(QDataStream::Qt_4_2);
  QString str;
  qint32 a;
  in >> str >> a;           // extract "the answer is" and 42
  qDebug()<<str<<a<<in.version();
  file2.close();
}

void MainWindow::initMenu (){

  openAction = new QAction(tr("&Open"), this);
  openAction->setShortcut(QKeySequence::Open);
  openAction->setStatusTip(tr("Open a file."));
  openAction->setIcon(QIcon(":/icon/res/open.png"));/// icon文件名是prefix+文件路径

  connect(openAction,SIGNAL(triggered()),this,SLOT(open()));

  quitAction = new QAction(tr("&Quit"), this);
  quitAction->setShortcut(QKeySequence::Quit);
  quitAction->setStatusTip(tr("Quit the program."));
  connect(quitAction,SIGNAL(triggered()),this,SLOT(quit()));

  QMenu *file = menuBar()->addMenu(trUtf8("&File"));/// \brief 菜单
  ui->menuBar->addMenu(file);
  file->addAction(openAction);
  file->addAction(quitAction);

  //  QToolBar *toolBar = addToolBar(tr("&File"));
  QPushButton *pbutton=new QPushButton();
  QIcon *icon=new QIcon(":/icon/res/a.png");
  pbutton->setIcon(*icon);
  pbutton->setShortcut(Qt::CTRL+Qt::Key_X);
  //  pbutton->setFlat(true);去除立体效果扁平风格
  ui->mainToolBar->addWidget(pbutton);/// \brief 工具栏
  ui->mainToolBar->addAction(openAction);

  ui->statusBar->showMessage("Ready! Go...",3);  /// \brief 状态栏
  //   ui->statusBar->addPermanentWidget(new QLabel(tr("statusBar状态栏")));
  //  ui->statusBar->insertWidget(100,new QLabel(tr("statusBar状态栏")),10);
  /// \attention insertWidget 和addWidget 会被临时消息给冲掉

  changeColorAction =new QAction("&ChangeColor",this);
  changeColorAction->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_C);
  changeColorAction->setToolTip("Change the color of window.");
  changeColorAction->setStatusTip("Change the color of window.");
  changeColorAction->setIcon(QIcon(":/icon/res/emotes/face-red.svg"));
  ui->mainToolBar->addAction(changeColorAction);
  connect(changeColorAction,SIGNAL(triggered()),this,SLOT(changeColor()));



}

///
/// @brief this function open file
///

void MainWindow::open(){
  qDebug()<<"disply open file dialog";
  ///
  /// \brief filePath  打开单个文件
  ///
  //    QString filePath = QFileDialog::getOpenFileName(this,
  //                                                    tr("Open Image"),
  //                                                    "/home/",
  //                                                    tr("Image Files list 1(*.jpg *.png);;Image Files list 2(*.bmp);;anything (*.*)"));

  //    if (filePath.length()>0)
  //        qDebug()<<"You choosed file "<<filePath;
  //    else
  //        qDebug()<<"You choosed nothing !!!";

  ///
  /// \brief filesPaths 打开多个文件
  ///
  QStringList filesPaths=QFileDialog::getOpenFileNames(this,
                                                       tr("Open Images"),
                                                       "/home/",
                                                       tr("anything (*.*);;Image Files list 1(*.jpg *.png);;Image Files list 2(*.bmp);;anything (*.*)"));

  if (filesPaths.length()<=0)
    qDebug()<<"You choosed nothing !!!";
  else
    {
      QStringList::Iterator iterator;
      for (iterator = filesPaths.begin(); iterator != filesPaths.end();
           ++iterator)
        {
          (*iterator)= (*iterator).simplified().trimmed();
          qDebug() << *iterator;
          QFile file(*iterator);
          if(!file.open(QIODevice::ReadOnly))
            {  qDebug() <<"Open filed"; return;}

          qDebug()<<"Open success , Reading now...";
          QDataStream stream( &file );
          stream.setVersion( QDataStream::Qt_4_2 );

          QString strMagicNumber;
          stream >> strMagicNumber;
          cenQWi->label_1->setText(strMagicNumber);

          file.close();
        }
    }
}
///
/// \brief MainWindow::changeColor 打开颜色选择对话框 
///
void MainWindow::changeColor(){
  ///
  /// \brief color 弹出颜色选择对话框
  ///
  QColor color = QColorDialog::getColor(Qt::blue,0,"choose the", 0);
  QString msg = QString("red: %1, green: %2, blue: %3").arg(QString::number(color.red()),
                                                            QString::number(color.green()),
                                                            QString::number(color.blue())
                                                            );
  qDebug()<<msg;

}
///
/// \brief MainWindow::quit 退出本程序,练习一下QMessageBox的使用
///
///
void MainWindow::quit(){
  this->close();
}

///
/// @brief This function make widget center of screen
///
/// @fn MainWindow::centerWidget
/// @param QWidget *w, bool useSizeHint
///

void MainWindow::centerWidget(QWidget *w, bool useSizeHint)
{
  if(w->isFullScreen())
    return;

  QSize size;
  if(useSizeHint)
    size = w->sizeHint();
  else
    size = w->size();

  QDesktopWidget *d = QApplication::desktop();
  int ws = d->width();   // returns screen width
  int h = d->height();  // returns screen height
  int mw = size.width();
  int mh = size.height();
  int cw = (ws/2) - (mw/2);
  int ch = (h/2) - (mh/2);
  w->move(cw,ch);
}

//void MainWindow::mouseMoveEvent(QMouseEvent *event){

//    QMessageBox *msg=new QMessageBox();
//    QString ss="MainWindow::mouseDoubleClickEvent()"+event->x();
//    msg->setText(ss);

//}

/// \brief 重写关闭窗口事件,提醒保存数据
///
void MainWindow::closeEvent( QCloseEvent * event )
{
  ///
  /// \note 这里使用的是静态方法,当然也可以使用构造函数重新生成一个实体
  ///
  QMessageBox::StandardButton result= QMessageBox::information(this,
                                                               "Attention Please!!!",
                                                               "Have you save your job before you QUIT !!!",
                                                               QMessageBox::Ok| QMessageBox::Cancel,QMessageBox::Cancel);

  switch(result)
    {
    case QMessageBox::Ok:event->accept();break;
    case QMessageBox::Cancel :event->ignore();break;
    default : event->ignore ();;
    }
}

/// \brief 最小化到系统状态栏
///
void MainWindow::changeEvent (QEvent *event){

  if(event->type() ==QEvent::WindowStateChange)
    {
      switch(this->windowState ()){
        case Qt::WindowMinimized:  this->hide(); event->ignore();break;
        default:    break;
        }
    }
}

/// \brief system tray
///
void MainWindow::setSystemIcon(){
  QAction *restoreAction,*quitAction;

  restoreAction = new QAction(tr("&Restore"), this);
  connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
  quitAction = new QAction(tr("&Quit"), this);
  connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));


  trayIconMenu = new QMenu(this);
  trayIconMenu->addAction(restoreAction);
  trayIconMenu->addSeparator();
  trayIconMenu->addAction(quitAction);

  trayIcon=new QSystemTrayIcon();
  trayIcon->setContextMenu (trayIconMenu);
  trayIcon->setIcon (QIcon::fromTheme("system-file-manager"));

  connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
          this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));


  trayIcon->show();

}

int clickTrayCount=0;

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
  switch (reason) {
    case QSystemTrayIcon::Trigger:this->showMessage();clickTrayCount++;break;
    case QSystemTrayIcon::DoubleClick:  this->showNormal ();break;
    case QSystemTrayIcon::Context:
    case QSystemTrayIcon::MiddleClick: clickTrayCount++; break;
    default:break;
    }
}

void MainWindow::showMessage()
{//const QString title, const QString msg,  MessageIcon icon = Information, int msecs = 10000
  QString message="Message___";
  char temp[100];
  sprintf(temp, "%d", clickTrayCount);
  message+=temp;
  trayIcon->showMessage("Message Title",message,QSystemTrayIcon::Information ,1000);

}

