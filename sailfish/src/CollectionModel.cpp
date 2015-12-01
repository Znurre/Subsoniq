#include <QDebug>
#include <QJsonObject>

#include "CollectionModel.h"
#include "CollectionRootNode.h"
#include "QStringEx.h"
#include "Key.h"
#include "ICollectionNodeProxy.h"
#include "NodeHelper.h"

CollectionModel::CollectionModel()
	: m_root(&m_scopedRoot)
	, m_status(Finished)
{

}

int CollectionModel::status() const
{
	return m_status;
}

void CollectionModel::setStatus(int status)
{
	m_status = status;

	emit statusChanged();
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

QModelIndex CollectionModel::index(int row, int column, const QModelIndex &parent) const
{
	ICollectionNode *parentNode = getNode(parent);
	ICollectionNode *childNode = parentNode->childAt(row);

	return createIndex(row, column, childNode);
}

QModelIndex CollectionModel::parent(const QModelIndex &child) const
{
	Q_UNUSED(child);

	return QModelIndex();
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
	ICollectionNode *node = getNode(parent);

	return node->hasChildren();
}

bool CollectionModel::canFetchMore(const QModelIndex &parent) const
{
	ICollectionNode *node = getNode(parent);

	return node->canFetchMore();
}

void CollectionModel::fetchMore(const QModelIndex &parent)
{
	setStatus(Loading);

	ICollectionNode *node = getNode(parent);

	if (node)
	{
		node->fetchMore();
	}

	setStatus(Finished);

	emit layoutChanged();
}

QString CollectionModel::getPageTitle(const QModelIndex &index) const
{
	Q_UNUSED(index);

	ICollectionNode *node = getNode(index);

	return node->title();
}

QObject *CollectionModel::getParentNode(const QModelIndex &index) const
{
	ICollectionNode *node = (ICollectionNode *)index.internalPointer();
	ICollectionNodeProxy *proxy = new ICollectionNodeProxy(node);

	return proxy;
}

ICollectionNode *CollectionModel::getNode(const QModelIndex &index) const
{
	return (ICollectionNode *)index.internalPointer() ?: m_root;
}
