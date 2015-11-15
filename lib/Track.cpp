#include "Track.h"

Track::Track(const QJsonObject &object)
	: m_object(object)
{

}

QString Track::id() const
{
	return m_object
		.value("id")
		.toString();
}

QString Track::artist() const
{
	return m_object
		.value("artist")
		.toString();
}

QString Track::title() const
{
	return m_object
		.value("title")
		.toString();
}

QString Track::coverArt() const
{
	return m_object
		.value("coverArt")
		.toString();
}

int Track::size() const
{
	return m_object
		.value("size")
		.toInt();
}

Track::operator QString() const
{
	return id();
}

