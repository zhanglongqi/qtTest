#ifndef MYQLABEL_H
#define MYQLABEL_H
#include <QWidget>
class QLabel;
class QPushButton;


class myQWi : public QWidget

{
  Q_OBJECT
public:
  myQWi(QWidget *parent = 0);
  ~myQWi();

  QPushButton *button_1;
  QLabel *label_1;
  QLabel *label_2;
  bool handlePaintEvent(QObject *obj, QEvent *eve);
  void initLayout();

public slots:
 // void button_1Clicked();
protected:
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  bool eventFilter(QObject *obj, QEvent *event);
  // void paintEvent(QPaintEvent *event);
};

#endif // MYQLABEL_H
