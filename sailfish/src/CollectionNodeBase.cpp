#include <QJsonArray>
#include <QThread>

#include "CollectionAlbumNode.h"
#include "CollectionNodeBase.h"

CollectionNodeBase::CollectionNodeBase(ICollectionNode *parent, int index)
	: m_parent(parent)
	, m_collectionNodeResolver(this)
	, m_fetches(0)
	, m_index(index)
{

}

CollectionNodeBase::~CollectionNodeBase()
{
	qDebug() << "~CollectionNodeBase()";

	qDeleteAll(m_children);
}

ICollectionNode *CollectionNodeBase::childAt(int index) const
{
	return m_children[index];
}

ICollectionNode *CollectionNodeBase::parent() const
{
	return m_parent;
}

Track *CollectionNodeBase::track()
{
	return nullptr;
}

int CollectionNodeBase::row() const
{
	return m_index;
}

int CollectionNodeBase::childCount() const
{
	return m_children.count();
}

bool CollectionNodeBase::hasChildren() const
{
	return !m_fetches || m_children.count();
}

bool CollectionNodeBase::canFetchMore() const
{
	return !m_fetches;
}

void CollectionNodeBase::fetchMore()
{
	m_fetches++;

	m_adapter.getMusicDirectory(id(), this, &CollectionNodeBase::response);
}

void CollectionNodeBase::response(const QJsonObject &envelope)
{
	int i = 0;

	const QJsonObject &directory = envelope
		.value("directory")
		.toObject();

	const QJsonArray &child = directory
		.value("child")
		.toArray();

	for (const QJsonValue &value : child)
	{
		const QJsonObject &object = value
			.toObject();

		ICollectionNode *node = m_collectionNodeResolver.resolve(object, i++);

		connect(node, &ICollectionNode::dataChanged, this, &ICollectionNode::dataChanged);

		m_children << node;
	}

	emit dataChanged(this);
}
