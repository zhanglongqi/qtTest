#include <myQWi.h>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QPicture>
#include <QMouseEvent>
#include <QString>
#include <QPointF>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QValidator>
///   \note 想要自定义控件也就是各种类，一定不能忘了构造函数和析构函数，
///         不然类体不完整

myQWi::myQWi(QWidget *parent):
  QWidget(parent)
{
  initLayout();
}
myQWi::~myQWi(){

}


void myQWi::initLayout (){

  label_1 =new QLabel(trUtf8("Nothing to display，汉字显示测试"),this,0);
  // label_1->setWordWrap(true);
  label_1->setMinimumWidth (300);//the word wrap make minimum width useless.
  label_1->installEventFilter(this);

  label_2 =new QLabel("label_2",this,0);
  label_2->setMinimumSize (800,600);
  label_2->installEventFilter(this);

  button_1 = new QPushButton(QIcon(":/icon/res/emotes/face-red.svg"),"test",0);
  button_1->setFixedWidth (60);

  // QWidget *topWidget=new QWidget();
  // QHBoxLayout *topLayout=new QHBoxLayout(topWidget);
  // topWidget->setFixedHeight(50);//layout have no fixed wight but widget have
  QHBoxLayout *topLayout=new QHBoxLayout();
  topLayout->addWidget (label_1);
  topLayout->addStretch (1);
  topLayout->addWidget (button_1);

  QGridLayout *cenLayout=new QGridLayout();
  cenLayout->addWidget (label_2);


  QVBoxLayout *mainLayout=new QVBoxLayout();
  mainLayout->addLayout (topLayout);
  mainLayout->addLayout (cenLayout);
  mainLayout->addStretch (1);

  this->setLayout (mainLayout);
}

void myQWi::mouseMoveEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
    qDebug() <<"mouseMoveEvent: "<< (QString("<center><h1>Move: (%1, %2)</h1></center>")
                                     .arg(QString::number(event->x()), QString::number(event->y())));
  qDebug()<<"I have no idea";
}

void myQWi::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
      qDebug() << "mousePressEvent  " + QString::number(event->x(),10);
    } else {
      qDebug() << "...";

    }
}

void myQWi::mouseReleaseEvent(QMouseEvent *event)
{
  QString msg;
  msg.sprintf("mouseReleaseEvent: (%d, %d)",
              event->x(), event->y());
  qDebug() <<(msg);
}

bool myQWi::eventFilter(QObject *obj, QEvent *event)
{
  if(obj==label_1)
    {
      if (event->type() == QEvent::MouseButtonPress)
        {
          QMouseEvent *mouse = static_cast<QMouseEvent*>(event);
          //  QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
          //  qDebug() << "eventFilter Key press" << keyEvent->key();
          qDebug() << "eventFilter Mouse press" << mouse->button();
          return true;
        } else {
          return false;
        }
    }
  if(obj==label_2)
    {
      if (event->type() == QEvent::Paint)
        {
          qDebug() << "eventFilter Paint" ;
          return handlePaintEvent(obj, event);
        } else {
          return false;
        }
    }
  else
    {
      return QWidget::eventFilter(obj,event);
    }

}

bool myQWi::handlePaintEvent(QObject *obj, QEvent *eve)
{
  // QPainter painter(static_cast<QWidget *>(obj));
  QPainter painter(label_2);
  painter.drawLine(80, 100, 650, 500);

  painter.setPen(Qt::red);
  painter.drawRect(10, 10, 100, 400);

  painter.setPen(QPen(Qt::blue, 5));
  painter.setBrush(Qt::blue);
  painter.drawArc(50, 10, 300, 500,-90*16,90*16);

  painter.setPen(QPen(QColor(10,100,100), 2.5));
  painter.drawText (50,20,trUtf8 ("Draw Text,中文张龙琦"));


  QPixmap pixmap;
  pixmap.load(":/icon/res/b.png");

  painter.setRenderHint(QPainter::Antialiasing, true);//打开防锯齿
  painter.drawPixmap (500,200,70,70,pixmap);

  painter.setRenderHint(QPainter::Antialiasing, false);
  painter.drawPixmap (600,200,70,70,pixmap);
}
