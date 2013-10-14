#include <QWidget>
#include <QState>
#include <QStateMachine>
#include <QPushButton>
#include <QSignalTransition>
#include <QPropertyAnimation>

void test0(){
  QPushButton *button = new QPushButton("Animated Button");
  button->show();

  QStateMachine *machine = new QStateMachine;

  QState *state1 = new QState(machine);
  QState *state2 = new QState(machine);

  state1->assignProperty(button, "geometry", QRect(250, 250, 200, 200));
  state2->assignProperty(button, "geometry", QRect(600, 600, 100, 100));
  machine->setInitialState(state1);

  QPropertyAnimation *propertyAnima =new QPropertyAnimation(button, "geometry");
  propertyAnima->setDuration (2000);
  QSignalTransition *transition1 = state1->addTransition(button, SIGNAL(clicked()), state2);
  transition1->addAnimation(propertyAnima);
  QSignalTransition *transition2 = state2->addTransition(button,SIGNAL(clicked()), state1);
  transition2->addAnimation(propertyAnima);

  machine->start();

}
