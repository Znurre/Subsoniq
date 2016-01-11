#ifndef REQUEST_H
#define REQUEST_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QMediaContent>
#include <QEventLoop>
#include <QWaitCondition>
#include <QMutexLocker>

#include "ResponseTransformerFactory.h"

class Request
{
	public:
		Request(QNetworkAccessManager &network, const QNetworkRequest &request);

		template<class TInstance, class TCallback>
		void callback(TInstance *instance, TCallback callback)
		{
			QEventLoop loop;
			QNetworkReply *reply = m_network.get(m_request);

			m_responseTransformerFactory
				.create(instance, callback, reply, &loop)
				.connect(reply, &QNetworkReply::finished, &IResponseTransformer::handle);

			loop.exec();
		}

		template<class TInstance, class TCallback>
		void asyncCallback(TInstance *instance, TCallback callback)
		{
			QNetworkReply *reply = m_network.get(m_request);

			m_responseTransformerFactory
				.create(instance, callback, reply, nullptr)
				.connect(reply, &QNetworkReply::finished, &IResponseTransformer::handle);
		}

		QNetworkReply *stream();

	private:
		QNetworkAccessManager &m_network;
		QNetworkRequest m_request;

		ResponseTransformerFactory m_responseTransformerFactory;
};
#endif // REQUEST_H
