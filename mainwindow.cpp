#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "resource_tree.h"

#include <iostream>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QAction>
#include <QIcon>

using namespace std;

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

    QVBoxLayout *l = new QVBoxLayout();
    _rightTree = new QTreeWidget();
    _rightTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(_rightTree, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(onCustomContextMenuRequested(const QPoint&)));
    QTextEdit *text = new QTextEdit();
    l->addWidget(text);
    text->setText("<color=\"red\"> adb </color>");
    l->addWidget(_rightTree);
    QTreeWidgetItem *root = new QTreeWidgetItem(_rightTree);
    root->setText(0, "D:\\t.txt");
    root->setData(0, Qt::UserRole, QVariant(11));
    //tree->addTopLevelItem()


       // view->resize(1024, 750);

    QWidget *w = new QWidget();
    w->setLayout(l);
    int idx = ui->stackedWidget->addWidget(w);
    ui->stackedWidget->setCurrentIndex(idx);

    _actDownload = new QAction(QIcon(":/pic/close2.png"), "下载(&M)");
    connect(_actDownload, SIGNAL(triggered(bool)), this, SLOT(onActDownload()));
    _rightTreeSelItem = new QList<QTreeWidgetItem*>();
    //exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{


}

void MainWindow::onCustomContextMenuRequested(const QPoint & pt)
{
    _rightTreeSelItem->clear();
    auto itemList = _rightTree->selectedItems();
    if (itemList.size() < 1 || nullptr == itemList.first())
    {
        return;
    }

    _rightTreeSelItem->append(itemList);
    int type = itemList.first()->type();
    QMenu menu(_rightTree);

    menu.addAction(_actDownload);

    // 修改显示点为全局位置
    menu.exec(_rightTree->mapToGlobal(pt));
}

void MainWindow::onActDownload()
{
    if (_rightTreeSelItem->size() < 1 || nullptr == _rightTreeSelItem->first())
    {
        return;
    }
    auto data = _rightTreeSelItem->first()->data(0, Qt::UserRole);
    cout<<"user data=" << data.toInt() << endl;
}

void MainWindow::ontime()
{
    QDateTime now = QDateTime::currentDateTime();
    _timeLabel->setText(now.toString());
}

void MainWindow::refreshTree()
{

}

