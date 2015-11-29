#include <QDebug>
#include <QJsonObject>

#include "CollectionModel.h"
#include "CollectionRootNode.h"
#include "QStringEx.h"
#include "Key.h"
#include "ICollectionNodeProxy.h"
#include "NodeHelper.h"

CollectionModel::CollectionModel()
	: m_kask(&m_root)
{

}

QHash<int, QByteArray> CollectionModel::roleNames() const
{
	return
	{
		{ Roles::ModelData, "modelData" },
		{ Roles::Title, "name" },
		{ Roles::Icon, "icon" },
		{ Roles::ViewTemplate, "viewTemplate" },
		{ Roles::CoverUrl, "coverUrl" },
		{ Roles::Grouping, "grouping" }
	};
}

void CollectionModel::response(const QJsonObject &envelope)
{
	Q_UNUSED(envelope);

	emit layoutChanged();
	emit statusChanged();
}

QModelIndex CollectionModel::index(int row, int column, const QModelIndex &parent) const
{
	ICollectionNode *parentNode = nullptr;

	if (!parent.isValid())
	{
		parentNode = m_kask;
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

	return QModelIndex();
}

QModelIndex CollectionModel::parent(const QModelIndex &child) const
{
	if (!child.isValid())
	{
		return QModelIndex();
	}

	ICollectionNode *childNode = (ICollectionNode *)child.internalPointer();
	ICollectionNode *parentNode = childNode->parent();

	if (!parentNode || parentNode == m_kask)
	{
		return QModelIndex();
	}

	return createIndex(parentNode->row(), 0, parentNode);
}

int CollectionModel::rowCount(const QModelIndex &parent) const
{
	ICollectionNode *parentNode;

	if (!parent.isValid())
	{
		parentNode = m_kask;
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

	switch (role)
	{
		case Roles::ModelData:
		{
			return QVariant::fromValue(node);
		}

		case Roles::Title:
		{
			return node->title();
		}

		case Roles::Icon:
		{
			return node->icon();
		}

		case Roles::ViewTemplate:
		{
			return node->viewTemplate();
		}

		case Roles::CoverUrl:
		{
			return NodeHelper::getCoverUrl(node, "64");
		}

		case Roles::Grouping:
		{
			return node->grouping();
		}
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

	return m_root.canFetchMore();
}

void CollectionModel::fetchMore(const QModelIndex &parent)
{
	ICollectionNode *node = (ICollectionNode *)parent.internalPointer();

	if (node)
	{
		node->fetchMore();
	}
	else
	{
		m_adapter.getIndexes(this, &CollectionModel::response);
	}
}

QString CollectionModel::getPageTitle(const QModelIndex &index) const
{
	Q_UNUSED(index);

	ICollectionNode *node = (ICollectionNode *)index.internalPointer();

	if (node)
	{
		return node->title();
	}

	return "Artists";
}

QObject *CollectionModel::getParentNode(const QModelIndex &index) const
{
	ICollectionNode *node = (ICollectionNode *)index.internalPointer();
	ICollectionNodeProxy *proxy = new ICollectionNodeProxy(node);

	return proxy;
}
