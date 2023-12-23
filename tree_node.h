#ifndef TREE_NODE_H
#define TREE_NODE_H
#include <QObject>
#include <QList>
#include <QVariant>

#include "my_enum.h"

class TreeNode: public QObject
{
    Q_OBJECT
public:
    TreeNode(const QList<QVariant> &data, TreeNodeType TreeNodeType, TreeNode *parent=nullptr);
    void AddChild(TreeNode *child);

    QList<TreeNode *> GetChildren();

    TreeNode *child(int row);
        int childCount() const;
        int columnCount() const;
        QVariant data(int column) const;
        int row() const;
        TreeNode *parent();
        TreeNodeType type();
private:
    QString _text;
        QList<TreeNode *> _children;
        TreeNode* _parent;
        TreeNodeType _treeNodeType;
         QList<QVariant> _itemData;
};

#endif // TREE_NODE_H
