#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

class QLabel;
class QTreeWidget;
class QAction;
class QTreeWidgetItem;

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

private:
    Ui::MainWindow *ui;
    QLabel *_timeLabel;
    QTreeWidget *_rightTree;
    QList<QTreeWidgetItem*> *_rightTreeSelItem;
    QAction *_actDownload;
};
#endif // MAINWINDOW_H
