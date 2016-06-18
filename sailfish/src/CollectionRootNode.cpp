#include <QDebug>
#include <QJsonArray>

#include "CollectionArtistNode.h"
#include "CollectionRootNode.h"
#include "CollectionModel.h"

CollectionRootNode::CollectionRootNode()
	: m_canFetchMore(true)
{
	qDebug() << "CollectionRootNode";
}

CollectionRootNode::~CollectionRootNode()
{
	qDebug() << "~CollectionRootNode()";

	qDeleteAll(m_children);
}

QIcon CollectionRootNode::icon() const
{
	return QIcon();
}

QString CollectionRootNode::title() const
{
	return "Artists";
}

QString CollectionRootNode::viewTemplate() const
{
	return QString::null;
}

QString CollectionRootNode::id() const
{
	return QString::null;
}

QString CollectionRootNode::grouping() const
{
	return QString::null;
}

ICollectionNode *CollectionRootNode::childAt(int index) const
{
	return m_children.value(index);
}

Track *CollectionRootNode::track()
{
	return nullptr;
}

int CollectionRootNode::childCount() const
{
	return m_children.count();
}

bool CollectionRootNode::hasChildren() const
{
	return true;
}

bool CollectionRootNode::canFetchMore() const
{
	return m_canFetchMore;
}

bool CollectionRootNode::fetchMore()
{
	m_adapter.getIndexes(this, &CollectionRootNode::response);

	return !m_children.isEmpty();
}

void CollectionRootNode::response(const QJsonObject &envelope)
{
	const QJsonObject &indexes = envelope
		.value("indexes")
		.toObject();

	const QJsonArray &index = indexes
		.value("index")
		.toArray();

	for (const QJsonValue &value : index)
	{
		const QJsonObject &section = value
			.toObject();

		const QString &name = section
			.value("name")
			.toString();

		const QJsonArray &artist = section
			.value("artist")
			.toArray();

		for (const QJsonValue &value : artist)
		{
			const QJsonObject &object = value
				.toObject();

			m_children << new CollectionArtistNode(name, object);
		}
	}

	m_canFetchMore = false;
}
