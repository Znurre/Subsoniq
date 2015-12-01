#include "CollectionTrackNode.h"
#include "QStringEx.h"

CollectionTrackNode::CollectionTrackNode(const QJsonObject &object)
	 : m_track(object)
	 , m_object(object)
{
	qDebug() << object;
}

QIcon CollectionTrackNode::icon() const
{
	return QIcon();
}

QString CollectionTrackNode::title() const
{
	const QJsonValue &track = m_object.value("track");
	const QJsonValue &title = m_object.value("title");

	return QStringEx::format("%1 - %2", track, title);
}

QString CollectionTrackNode::viewTemplate() const
{
	return "TrackTemplate.qml";
}

QString CollectionTrackNode::id() const
{
	return QString::null;
}

QString CollectionTrackNode::grouping() const
{
	return QString::null;
}

ICollectionNode *CollectionTrackNode::childAt(int index) const
{
	Q_UNUSED(index);

	return nullptr;
}

Track *CollectionTrackNode::track()
{
	return &m_track;
}

int CollectionTrackNode::childCount() const
{
	return 0;
}

bool CollectionTrackNode::hasChildren() const
{
	return false;
}

bool CollectionTrackNode::canFetchMore() const
{
	return false;
}

void CollectionTrackNode::fetchMore()
{

}
