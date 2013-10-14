#ifndef TEST_H
#define TEST_H

#include <QMainWindow>
#include <QVBoxLayout>
class test : public QMainWindow
{
  Q_OBJECT
public:
  test(QMainWindow *parent = 0);
  ~test();
  QWidget *centWid;
 QVBoxLayout *mainlayout;
 void testLineEdit();

  void testRegularExpression();
  void testOutput();
  void testTimeline();
};

#endif // TEST_H
