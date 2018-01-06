#include <QVariant>

#include "QStringEx.h"
#include "Track.h"

StringToken::StringToken(const QString &value)
{
	m_value = value;
}

StringToken::StringToken(const int value)
{
	m_value = QString::number(value);
}

StringToken::StringToken(const QByteArray &value)
{
	m_value = QString::fromUtf8(value);
}

StringToken::StringToken(const QJsonValue &value)
{
	const QVariant &variant = value.toVariant();

	m_value = variant.toString();
}

StringToken::StringToken(const Track *track)
{
	const QString &artist = track->artist();
	const QString &title = track->title();

	m_value = QStringEx::format("%1 - %2", artist, title);
}


StringToken::operator QString() const
{
	return m_value;
}
