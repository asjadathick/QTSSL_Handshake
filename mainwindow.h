#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

namespace Ui {
   class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT
public:
   explicit MainWindow(QWidget *parent = 0);
private slots:
   void handleButton();
private:
   QPushButton *m_button;
   QLabel *q_label;
   QLineEdit *hostIn;
   QLineEdit *portIn;
};

#endif // MAINWINDOW_H
