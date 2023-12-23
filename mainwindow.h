#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

class QLabel;
class QTreeWidget;
class QAction;
class QTreeWidgetItem;
class TreeNode;
class ThreeDItemModel;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Init();

public slots:
    void ontime();
    void refreshTree();
    void onCustomContextMenuRequested(const QPoint&);
    void onActDownload();
    void onLeftTreeSelect(const QModelIndex&, const QModelIndex &);

private:
    Ui::MainWindow *ui;
    QLabel *_timeLabel;
    QTreeWidget *_rightTree;
    QList<QTreeWidgetItem*> *_rightTreeSelItem;
    QAction *_actDownload;

    ThreeDItemModel *_modelDesign;
    TreeNode *_nodeDesign;
    QLabel * _rightDesingLabel; // 右侧显示设计图的

};
#endif // MAINWINDOW_H
