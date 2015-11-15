#ifndef REQUESTFACTORY_H
#define REQUESTFACTORY_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "UrlBuilder.h"
#include "Request.h"
#include "Key.h"
#include "Settings.h"

class Settings;

class RequestFactory : public QObject
{
	public:
		RequestFactory(QObject *parent);

		template<class ...T>
		Request request(const QString &method, T... arguments)
		{
			const QList<api::KeyValue> keys =
			{
				// Method specific arguments
				arguments...,

				// Default arguments
				api::u = m_settings.username(),
				api::p = m_settings.password(),
				api::v = "1.12.0",
				api::c = "subsoniq",
				api::f = "json"
			};

			const QString &url = m_urlBuilder.build(method, keys);
			const QNetworkRequest request(url);

			qDebug() << url;

			return Request(m_network, request);
		}

	private:
		void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

		QNetworkAccessManager m_network;

		Settings m_settings;
		UrlBuilder m_urlBuilder;
};

#endif // REQUESTFACTORY_H
