#include "RequestFactory.h"

RequestFactory::RequestFactory(QObject *parent, Settings &settings)
	: m_network(parent)
	, m_settings(settings)
	, m_urlBuilder(settings)
{
	connect(&m_network, &QNetworkAccessManager::sslErrors, this, &RequestFactory::sslErrors);
}

void RequestFactory::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
	Q_UNUSED(errors);

	reply->ignoreSslErrors();
}
