#ifndef RESOURCE_TREE_H
#define RESOURCE_TREE_H

#include <QAbstractItemModel>

#include "tree_node.h"

// ref  https://doc.qt.io/qt-6/qtwidgets-itemviews-simpletreemodel-example.html
class ThreeDItemModel: public QAbstractItemModel
{
    Q_OBJECT
public:
    ThreeDItemModel(QObject *parent, TreeNode *root);

    Qt::ItemFlags flags(const QModelIndex &index) const override;

     virtual QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const;
     virtual QModelIndex parent(const QModelIndex &child) const;

     virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
     virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

     virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
    TreeNode *_root;
};

#endif // RESOURCE_TREE_H
