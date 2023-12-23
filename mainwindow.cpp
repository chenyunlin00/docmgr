#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "resource_tree.h"
#include "tree_node.h"

#include <iostream>
#include <QItemSelectionModel>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QAction>
#include <QIcon>
#include <QDir>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->centralwidget->setLayout(ui->verticalLayout);
    Init();
    _timeLabel = new QLabel();
    QTimer *timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(ontime()));
    ui->statusbar->layout()->addWidget(_timeLabel);
    timer->start();
    //ThreeDItemModel *model = new ThreeDItemModel(this);
    ui->treeView->setModel(_modelDesign);

    QVBoxLayout *l = new QVBoxLayout();
    _rightTree = new QTreeWidget();
    _rightTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(_rightTree, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(onCustomContextMenuRequested(const QPoint&)));
    _rightDesingLabel = new QLabel();
    l->addWidget(_rightDesingLabel);
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

    //connect
    connect(
                ui->treeView->selectionModel(),
            SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
            this,
            SLOT(onLeftTreeSelect(const QModelIndex &, const QModelIndex &))
   );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    _nodeDesign = new TreeNode({"设计数据库"}, TreeNodeType::DESIGN_DATABASE_ROOT);
    auto desingDB = new TreeNode({"设计数据库"}, TreeNodeType::DESIGN_DATABASE, _nodeDesign);
    _nodeDesign->AddChild(desingDB);
    auto frontRoomUnit = new TreeNode({"前部水室内部套"}, TreeNodeType::UNIT, desingDB);
    desingDB->AddChild(frontRoomUnit);
    auto waterInComponent = new TreeNode({"海水入口封头"}, TreeNodeType::COMPONENT, frontRoomUnit);
    frontRoomUnit->AddChild(waterInComponent);
    auto waterInComponentGraph = new TreeNode({"设计图"}, TreeNodeType::DESIGN_GRAPH, waterInComponent);
    waterInComponent->AddChild(waterInComponentGraph);
    auto waterInCalculateResult = new TreeNode({"分析计算结果"}, TreeNodeType::CALCULATE_RESULT, waterInComponent);
    waterInComponent->AddChild(waterInCalculateResult);


    _modelDesign = new ThreeDItemModel(nullptr, _nodeDesign);


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

void MainWindow::onLeftTreeSelect(const QModelIndex& cur, const QModelIndex &pre)
{
    TreeNode *item = static_cast<TreeNode*>(cur.internalPointer());
    cout << "user selection " << item->data(0).toString().toStdString() << endl;
    QDir dir = QDir(QApplication::applicationDirPath());
    dir.cd("pic");
    _rightDesingLabel->setPixmap(QPixmap(dir.filePath("design_sample.png")));
}

void MainWindow::ontime()
{
    QDateTime now = QDateTime::currentDateTime();
    _timeLabel->setText(now.toString("yyyy-MM-dd hh:mm:ss"));
}

void MainWindow::refreshTree()
{

}

