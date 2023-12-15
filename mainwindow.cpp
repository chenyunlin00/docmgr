#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "resource_tree.h"

#include <QLabel>
#include <QTimer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _timeLabel = new QLabel();
    QTimer *timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(ontime()));
    ui->statusbar->layout()->addWidget(_timeLabel);
    timer->start();
    ThreeDItemModel *model = new ThreeDItemModel(this);
    ui->treeView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ontime()
{
    QDateTime now = QDateTime::currentDateTime();
    _timeLabel->setText(now.toString());
}

void MainWindow::refreshTree()
{

}

