#include "RequestFactory.h"

RequestFactory::RequestFactory(QObject *parent)
	: m_network(parent)
	, m_urlBuilder(m_settings)
{
	connect(&m_network, &QNetworkAccessManager::sslErrors, this, &RequestFactory::sslErrors);
}

void RequestFactory::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
	Q_UNUSED(errors);

	reply->ignoreSslErrors();
}
