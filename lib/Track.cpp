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

QString Track::album() const
{
	return m_object
		.value("album")
		.toString();
}

int Track::duration() const
{
	return m_object
		.value("duration")
		.toInt();
}

int Track::size() const
{
	return m_object
		.value("size")
		.toInt();
}

int Track::track() const
{
	return m_object
		.value("track")
		.toInt();
}

Track::operator QString() const
{
	return id();
}

