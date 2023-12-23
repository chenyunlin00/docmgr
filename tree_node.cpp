#include "tree_node.h"


TreeNode::TreeNode(const QList<QVariant> &data, TreeNodeType treeNodeType, TreeNode *parent)
{
    _itemData = data;
    _treeNodeType = treeNodeType;
    _parent = parent;
}

void TreeNode::AddChild(TreeNode *child)
{
    _children.append(child);
}

QList<TreeNode *> TreeNode::GetChildren()
{
    return _children;
}

TreeNode *TreeNode::child(int row)
{
    if (row < 0 || row >= _children.size())
        return nullptr;
    return _children.at(row);
}

int TreeNode::childCount() const
{
    return _children.count();
}

int TreeNode::row() const
{
    if (_parent)
        return _parent->_children.indexOf(const_cast<TreeNode*>(this));

    return 0;
}

int TreeNode::columnCount() const
{
    return _itemData.count();
}

QVariant TreeNode::data(int column) const
{
    if (column < 0 || column >= _itemData.size())
        return QVariant();
    return _itemData.at(column);
}

TreeNode *TreeNode::parent()
{
    return _parent;
}

TreeNodeType TreeNode::type()
{
    return _treeNodeType;
}

