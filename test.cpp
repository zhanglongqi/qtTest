#include "test.h"
#include <QPushButton>
#include <QLineEdit>
#include <QValidator>
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>
#include <vector>
#include <QVector>
#include <QRegExp>
#include <QLabel>
#include <QTime>
#include <QtCore/QCoreApplication>
#include <QTimer>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <QTimeLine>
#include <QProgressBar>
test::test(QMainWindow *parent )
  :QMainWindow(parent)
{
  centWid = new QWidget();
  setCentralWidget (centWid);
  mainlayout =new QVBoxLayout();
  centWid->setLayout (mainlayout);
  //  testLineEdit ();
  //testRegularExpression();
  testTimeline ();
}
test::~test (){

}
void test::testLineEdit(){
  QLineEdit * edit = new QLineEdit(this);
  edit->setAlignment(Qt::AlignRight);
  // QRegExp rxHex("^[0-9A-F]{3}$",Qt::CaseInsensitive);
  QValidator *validatorHex = new QRegExpValidator(QRegExp("^[0-9A-F]{3}$",Qt::CaseInsensitive), this);
  edit->setValidator (validatorHex);

  QPushButton *button_1 = new QPushButton("button_1",this);
  QVBoxLayout *mainLayout=new QVBoxLayout();
  mainLayout->addWidget (edit);
  mainLayout->addWidget (button_1);


  QWidget *cen = new QWidget();
  this->setCentralWidget (cen);
  cen->setLayout (mainLayout);

}

void test::testRegularExpression ()
{

  QRegExp rx("^\\d\\d?$");    // match integers 0 to 99

  qDebug()<< rx.indexIn("123");   // returns -1 (no match)

  qDebug()<< rx.indexIn("-6");  // returns -1 (no match)

  qDebug()<< rx.indexIn("6"); // returns 0 (matched as position 0)
  qDebug()<< rx.capturedTexts ();
  qDebug()<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*";
  QRegExp *re1 = new QRegExp();
  QString test = "My IP is 110:1:1:2,My name is zhang , my birthday is 0821";

  re1->setPattern ("\\d{1,3}:\\d{1,3}:\\d{1,3}:\\d{1,3}");
  if (!re1->isValid ()) return;
  qDebug()<<re1->indexIn (test);

  qDebug()<<test.indexOf (*re1)<< "  "<< re1->capturedTexts ();

  qDebug()<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*";
  re1->setPattern ("\\d{3}");
  if (!re1->isValid ()) return;

  qDebug()<<test
         <<re1->indexIn (test)
        <<re1->captureCount ()
       << "  "<<re1->pattern ()
       << "  "<< re1->matchedLength ()
       << "  "<< re1->capturedTexts ();

  test="[122]";
  re1->setPattern ("\\[\\d{3}\\]");

  qDebug()<<"**********************"
         <<test
        <<re1->indexIn (test);

}

void test::testOutput ()
{
  // QCoreApplication app(argc, argv); //renamed the a to app
  QTextStream qout(stdout); //I connect the stout to my qout textstream

  qout <<     "1. Starting the application\n";
  std::cout << "2. Some normal iostream output before using qDebug\n";
  qDebug() << "3. Some output with qDebug after the iostream output\n";
  //  qDebug("Items in list: %d,%s", argc,argv[0]);
  //  QTimer::singleShot(5000, &app, SLOT(quit())); //stop after 5 seconds
}

void test::testTimeline(){
QProgressBar *progressBar = new QProgressBar();
progressBar->setRange(0, 1000);

// Construct a 1-second timeline with a frame range of 0 - 100
QTimeLine *timeLine = new QTimeLine(1000, this);
timeLine->setFrameRange(0, 1000);
timeLine->setCurveShape (QTimeLine::LinearCurve);
//timeLine->setDirection (QTimeLine::Backward);
connect(timeLine, SIGNAL(frameChanged(int)), progressBar, SLOT(setValue(int)));

// Clicking the push button will start the progress bar animation
QPushButton *pushButton = new QPushButton(tr("Start animation"));
connect(pushButton, SIGNAL(clicked()), timeLine, SLOT(start()));
mainlayout->addWidget (progressBar);
mainlayout->addWidget (pushButton);
}
