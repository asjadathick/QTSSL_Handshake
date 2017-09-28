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

    q_label = new QLabel("Handshake information", this);
    q_label->setGeometry(QRect(QPoint(100, 250),
    QSize(1000, 350)));

    hostIn = new QLineEdit("www.google.com", this);
    hostIn->setGeometry(QRect(QPoint(100, 600),
    QSize(200, 50)));

    portIn = new QLineEdit("443", this);
    portIn->setGeometry(QRect(QPoint(350, 600),
    QSize(50, 50)));

    // Connect button signal to appropriate slot
    connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));
 }

 void MainWindow::handleButton()
 {
     char *inputs[3];
     inputs[0]="ssl";
     inputs[1] = new char[500];
     strcpy(inputs[1], hostIn->text().toStdString().c_str());
     inputs[2] = new char[500];
     strcpy(inputs[2], portIn->text().toStdString().c_str());

    q_label->setText("Performing handshake");
    std::string temp = performHandshake(3, inputs);
    q_label->setText(temp.c_str());
    m_button->setText("Re-negotiate handshake");

    delete inputs[1];
    delete inputs[2];

 }
