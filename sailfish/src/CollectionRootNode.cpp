#include <QDebug>
#include <QJsonArray>

#include "CollectionArtistNode.h"
#include "CollectionRootNode.h"

CollectionRootNode::CollectionRootNode(const QJsonObject &root)
	: m_root(root)
{
	int i = 0;

	const QJsonObject &indexes = root
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

			ICollectionNode *node = new CollectionArtistNode(name, object, this, i++);

			connect(node, &ICollectionNode::dataChanged, this, &ICollectionNode::dataChanged);

			m_children << node;
		}
	}
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
	return "Collection";
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
	return m_children[index];
}

ICollectionNode *CollectionRootNode::parent() const
{
	return nullptr;
}

Track *CollectionRootNode::track()
{
	return nullptr;
}

int CollectionRootNode::row() const
{
	return 0;
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
	return false;
}

void CollectionRootNode::fetchMore()
{

}
