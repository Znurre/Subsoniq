#include <QJsonArray>
#include <QThread>

#include "CollectionAlbumNode.h"
#include "CollectionNodeBase.h"
#include "CollectionModel.h"

CollectionNodeBase::CollectionNodeBase()
	: m_canFetchMore(true)
{

}

CollectionNodeBase::~CollectionNodeBase()
{
	qDebug() << "~CollectionNodeBase()";

	qDeleteAll(m_children);
}

ICollectionNode *CollectionNodeBase::childAt(int index) const
{
	return m_children.value(index);
}

Track *CollectionNodeBase::track()
{
	return nullptr;
}

int CollectionNodeBase::childCount() const
{
	return m_children.count();
}

bool CollectionNodeBase::hasChildren() const
{
	return m_children.count();
}

bool CollectionNodeBase::canFetchMore() const
{
	return m_canFetchMore;
}

bool CollectionNodeBase::fetchMore()
{
	m_adapter.getMusicDirectory(id(), this, &CollectionNodeBase::response);

	return !m_children.isEmpty();
}

void CollectionNodeBase::response(const QJsonObject &envelope)
{
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

		m_children << m_collectionNodeResolver.resolve(object);
	}

	m_canFetchMore = false;
}
