#include <QJsonArray>

#include "CollectionAlbumNode.h"
#include "CollectionNodeBase.h"
#include "CollectionModel.h"

CollectionNodeBase::CollectionNodeBase(CollectionModel *model, ICollectionNode *parent, int index)
	: m_model(model)
	, m_parent(parent)
	, m_collectionNodeResolver(model, this)
	, m_fetches(0)
	, m_index(index)
{
}

CollectionNodeBase::~CollectionNodeBase()
{
	qDeleteAll(m_children);
}

ICollectionNode *CollectionNodeBase::childAt(int index) const
{
	return m_children.value(index);
}

ICollectionNode *CollectionNodeBase::parent() const
{
	return m_parent;
}

const Track *CollectionNodeBase::track() const
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

void CollectionNodeBase::raiseDataChanged()
{
	const QModelIndex index = m_model->createIndex(m_index, 0, this);

	emit m_model->dataChanged(index, index);
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

	const QModelIndex index = m_model->createIndex(m_index, 0, this);

	m_model->beginInsertRows(index, 0, child.count() - 1);

	for (const QJsonValue &value : child)
	{
		const QJsonObject &object = value
			.toObject();

		m_children << m_collectionNodeResolver.resolve(object, i++);
	}

	m_model->endInsertRows();
}
