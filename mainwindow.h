#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
/// \attention In the header file, "#include" is used only it's inherited or
/// you are not using a pointer or reference to declare a variable.
/// you should use "class AAA" in the other situation
///

class QAction;
class myQWi;
class QSystemTrayIcon;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void centerWidget(QWidget *w, bool useSizeHint);
  myQWi *cenQWi;

  QSystemTrayIcon *trayIcon;
  QMenu *trayIconMenu;

private:
  Ui::MainWindow *ui;
  QAction *openAction;
  QAction *quitAction;
  QAction *changeColorAction;
  void initMenu();
  void fileRWTest();
  void closeEvent (QCloseEvent *);
  void changeEvent (QEvent *);
  void setSystemIcon();
  void showMessage();

private slots:
  void open();
  void changeColor();
  void quit();
  void iconActivated(QSystemTrayIcon::ActivationReason reason);

};

#endif // MAINWINDOW_H
