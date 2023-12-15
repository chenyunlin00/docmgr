#include "resource_tree.h"



ThreeDItemModel::ThreeDItemModel(QObject *parent): QAbstractItemModel(parent)
{

}

QModelIndex ThreeDItemModel::index(int row, int column,
                  const QModelIndex &parent) const
{
    return this->createIndex(row, column);
}


QModelIndex ThreeDItemModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int ThreeDItemModel::rowCount(const QModelIndex &parent) const
{
    return 10;
}


int ThreeDItemModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant ThreeDItemModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
            return QVariant();
    return QVariant(QString("汽车模型"));
}
