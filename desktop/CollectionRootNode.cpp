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

		const QJsonArray &artist = section
			.value("artist")
			.toArray();

		for (const QJsonValue &value : artist)
		{
			const QJsonObject &object = value
				.toObject();

			ICollectionNode *node = new CollectionArtistNode(object, this, i++);

			connect(node, &ICollectionNode::dataChanged, this, &ICollectionNode::dataChanged);

			m_children << node;
		}
	}
}

CollectionRootNode::~CollectionRootNode()
{
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

QSize CollectionRootNode::sizeHint() const
{
	return QSize();
}

ICollectionNode *CollectionRootNode::childAt(int index) const
{
	return m_children[index];
}

ICollectionNode *CollectionRootNode::parent() const
{
	return nullptr;
}

const Track *CollectionRootNode::track() const
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
