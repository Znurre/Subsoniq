#include <QDebug>
#include <QJsonObject>

#include "CollectionModel.h"
#include "CollectionRootNode.h"
#include "QStringEx.h"
#include "Key.h"
#include "ICollectionNodeProxy.h"

CollectionModel::CollectionModel()
	: m_root(nullptr)
	, m_status(Loading)
{
	m_adapter.getIndexes(this, &CollectionModel::response);
}

CollectionModel::~CollectionModel()
{
	qDebug() << "~CollectionModel()";

	delete m_root;
}

int CollectionModel::status() const
{
	return m_status;
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
	m_root = new CollectionRootNode(envelope);
	m_status = Finished;

	connect(m_root, &ICollectionNode::dataChanged, this, &CollectionModel::nodeExpanded);

	emit layoutChanged();
	emit statusChanged();
}

void CollectionModel::nodeExpanded(ICollectionNode *node)
{
//	const QModelIndex &index = createIndex(node->row(), 0, node);
//	const QList<QPersistentModelIndex> indexes =
//	{
//		index
//	};

//	emit layoutChanged(indexes);
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
			const QString &id = node->id();
			const QString &url = QStringEx::format("image://cover/%1", id);

			return url;
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
