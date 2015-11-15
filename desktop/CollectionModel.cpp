#include <QDebug>
#include <QJsonObject>

#include "CollectionModel.h"
#include "CollectionRootNode.h"
#include "Key.h"

CollectionModel::CollectionModel()
	: m_root(nullptr)
{
	m_adapter.getIndexes(this, &CollectionModel::response);
}

CollectionModel::~CollectionModel()
{
	delete m_root;
}

void CollectionModel::response(const QJsonObject &envelope)
{
	m_root = new CollectionRootNode(envelope);

	connect(m_root, &ICollectionNode::dataChanged, this, &CollectionModel::nodeExpanded);

	emit layoutChanged();
}

void CollectionModel::nodeExpanded(ICollectionNode *node)
{
	const QModelIndex &index = createIndex(node->row(), 0, node);
	const QList<QPersistentModelIndex> indexes =
	{
		index
	};

	emit layoutChanged(indexes);
}

QModelIndex CollectionModel::index(int row, int column, const QModelIndex &parent) const
{
	if (!hasIndex(row, column, parent))
	{
		return QModelIndex();
	}

	ICollectionNode *parentNode = nullptr;

	if (!parent.isValid())
	{
		parentNode = m_root;
	}
	else
	{
		parentNode = (ICollectionNode *)parent.internalPointer();
	}

	if (!parentNode)
	{
		return QModelIndex();
	}

	ICollectionNode *childNode = parentNode->childAt(row);

	if (childNode)
	{
		return createIndex(row, column, childNode);
	}
	else
	{
		return QModelIndex();
	}
}

QModelIndex CollectionModel::parent(const QModelIndex &child) const
{
	if (!child.isValid())
	{
		return QModelIndex();
	}

	ICollectionNode *childNode = (ICollectionNode *)child.internalPointer();
	ICollectionNode *parentNode = childNode->parent();

	if (!parentNode || parentNode == m_root)
	{
		return QModelIndex();
	}

	return createIndex(parentNode->row(), 0, parentNode);
}

int CollectionModel::rowCount(const QModelIndex &parent) const
{
	if (parent.column() > 0)
	{
		return 0;
	}

	ICollectionNode *parentNode;

	if (!parent.isValid())
	{
		parentNode = m_root;
	}
	else
	{
		parentNode = (ICollectionNode *)parent.internalPointer();
	}

	if (!parentNode)
	{
		return 0;
	}

	return parentNode->childCount();
}

int CollectionModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return 1;
}

QVariant CollectionModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	ICollectionNode *node = (ICollectionNode *)index.internalPointer();

	if (role == Qt::DecorationRole)
	{
		return node->icon();
	}

	if (role == Qt::DisplayRole)
	{
		return node->title();
	}

	if (role == Qt::SizeHintRole)
	{
		return node->sizeHint();
	}

	return QVariant();
}

bool CollectionModel::hasChildren(const QModelIndex &parent) const
{
	ICollectionNode *node = (ICollectionNode *)parent.internalPointer();

	if (node)
	{
		return node->hasChildren();
	}

	return true;
}

bool CollectionModel::canFetchMore(const QModelIndex &parent) const
{
	ICollectionNode *node = (ICollectionNode *)parent.internalPointer();

	if (node)
	{
		return node->canFetchMore();
	}

	return false;
}

void CollectionModel::fetchMore(const QModelIndex &parent)
{
	ICollectionNode *node = (ICollectionNode *)parent.internalPointer();

	if (node)
	{
		node->fetchMore();
	}
}

