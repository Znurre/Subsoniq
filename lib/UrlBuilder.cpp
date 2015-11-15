#include "UrlBuilder.h"
#include "QStringEx.h"
#include "QueryBuilder.h"
#include "Settings.h"

UrlBuilder::UrlBuilder(Settings &settings)
	: m_settings(settings)
{

}

QString UrlBuilder::build(const QString &method, const QList<api::KeyValue> &keys) const
{
	QueryBuilder queryBuilder;
	queryBuilder.setParameters(keys);

	const QString &baseUrl = m_settings.serverUrl();
	const QString &arguments = queryBuilder.build();
	const QString &url = QStringEx::format("%1/rest/%2?%3", baseUrl, method, arguments);

	return url;
}

