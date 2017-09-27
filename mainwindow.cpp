#include "mainwindow.h"
#include "ssl.h"
#include <QCoreApplication>


 MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
 {
    // Create the button, make "this" the parent
    m_button = new QPushButton("Perform handshake", this);
    // set size and location of the button
    m_button->setGeometry(QRect(QPoint(100, 100),
    QSize(200, 50)));

    q_label = new QLabel("Label", this);
    q_label->setGeometry(QRect(QPoint(100, 250),
    QSize(1000, 350)));

    // Connect button signal to appropriate slot
    connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));
 }

 void MainWindow::handleButton()
 {
     char *inputs[]={"ssl","facebook.com","443"};
    q_label->setText("Performing handshake");
    std::string temp = performHandshake(3, inputs);
    q_label->setText(temp.c_str());
    m_button->setText("Re-negotiate handshake");

 }
