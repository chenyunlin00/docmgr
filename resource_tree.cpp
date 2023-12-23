#include "resource_tree.h"
#include "my_constant.h"
#include <QIcon>
#include <QApplication>
#include <QDir>


ThreeDItemModel::ThreeDItemModel(QObject *parent, TreeNode *root): QAbstractItemModel(parent)
{
    _root = root;
}

QModelIndex ThreeDItemModel::index(int row, int column,
                  const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
           return QModelIndex();

       TreeNode *parentItem;

       if (!parent.isValid())
           parentItem = _root;
       else
           parentItem = static_cast<TreeNode*>(parent.internalPointer());

       TreeNode *childItem = parentItem->child(row);
       if (childItem)
           return createIndex(row, column, childItem);
       return QModelIndex();
}


QModelIndex ThreeDItemModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
            return QModelIndex();

        TreeNode *childItem = static_cast<TreeNode*>(index.internalPointer());
        TreeNode *parentItem = childItem->parent();

        if (parentItem == _root)
            return QModelIndex();

        return createIndex(parentItem->row(), 0, parentItem);
}

int ThreeDItemModel::rowCount(const QModelIndex &parent) const
{
    TreeNode *parentItem;
        if (parent.column() > 0)
            return 0;

        if (!parent.isValid())
            parentItem = _root;
        else
            parentItem = static_cast<TreeNode*>(parent.internalPointer());

        return parentItem->childCount();
}


int ThreeDItemModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
            return static_cast<TreeNode*>(parent.internalPointer())->columnCount();
        return _root->columnCount();
}

QVariant ThreeDItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();

    TreeNode *item = static_cast<TreeNode*>(index.internalPointer());

    if ( role == Qt::DecorationRole ) {

        QIcon icon;

        if (item->type() == TreeNodeType::DESIGN_DATABASE)
        {
            icon.addPixmap(QPixmap(ICON_PATH_DB));
        }
        else if (item->type() == TreeNodeType::DESIGN_GRAPH)
        {
            icon.addPixmap(QPixmap(ICON_PATH_DESIGN_GRAPH));
        }
        else if (item->type() == TreeNodeType::CALCULATE_RESULT)
        {
            icon.addPixmap(QPixmap(ICON_PATH_CALCULATE_RESULT));
        }
        else
        {
            icon.addPixmap(QPixmap(ICON_PATH_DEFAULT));
        }

        return icon;
    }

        if (role != Qt::DisplayRole)
            return QVariant();



        return item->data(index.column());
}

Qt::ItemFlags ThreeDItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}
