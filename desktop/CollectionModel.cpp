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
	m_root = new CollectionRootNode(envelope, this);

	emit layoutChanged();
}

QModelIndex CollectionModel::index(int row, int column, const QModelIndex &parent) const
{
	ICollectionNode *parentNode = getNode(parent);
	ICollectionNode *childNode = parentNode->childAt(row);

	return createIndex(row, column, childNode);
}

QModelIndex CollectionModel::parent(const QModelIndex &child) const
{
	ICollectionNode *childNode = (ICollectionNode *)child.internalPointer();

	if (!childNode)
	{
		return QModelIndex();
	}

	ICollectionNode *parentNode = childNode->parent();

	if (!parentNode || parentNode == m_root)
	{
		return QModelIndex();
	}

	return createIndex(parentNode->row(), 0, parentNode);
}

int CollectionModel::rowCount(const QModelIndex &parent) const
{
	ICollectionNode *node = getNode(parent);

	return node->childCount();
}

int CollectionModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return 1;
}

QVariant CollectionModel::data(const QModelIndex &index, int role) const
{
	ICollectionNode *node = (ICollectionNode *)index.internalPointer();

	if (!node)
	{
		return QVariant();
	}

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

ICollectionNode *CollectionModel::getNode(const QModelIndex &index) const
{
	return (ICollectionNode *)index.internalPointer() ?: m_root;
}
