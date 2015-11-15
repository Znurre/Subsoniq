#include "Request.h"

Request::Request(QNetworkAccessManager &network, const QNetworkRequest &request)
	: m_network(network)
	, m_request(request)
{

}

QNetworkReply *Request::stream()
{
	return m_network.get(m_request);
}
