#ifndef URLBUILDER_H
#define URLBUILDER_H

#include <QString>

#include "KeyValue.h"

class Settings;

class UrlBuilder
{
	public:
		UrlBuilder(Settings &settings);

		QString build(const QString &method, const QList<api::KeyValue> &keys) const;

	private:
		Settings &m_settings;
};

#endif // URLBUILDER_H
