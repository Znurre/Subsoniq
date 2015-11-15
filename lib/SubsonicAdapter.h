#ifndef SUBSONICADAPTER_H
#define SUBSONICADAPTER_H

#include <QString>
#include <QMediaContent>

#include "ResponseCallback.h"
#include "RequestFactory.h"
#include "Settings.h"

class SubsonicAdapter : public QObject
{
	Q_OBJECT

	public:
		SubsonicAdapter(QObject *parent = 0)
			: m_requestFactory(parent)
		{

		}

		template<class TInstance>
		void getIndexes(TInstance *instance, JsonCallback<TInstance> callback)
		{
			m_requestFactory
				.request("getIndexes.view")
				.callback(instance, callback);
		}

		template<class TInstance>
		void getMusicDirectory(const QString &id, TInstance *instance, JsonCallback<TInstance> callback)
		{
			m_requestFactory
				.request("getMusicDirectory.view"
					, api::id = id)
				.callback(instance, callback);
		}

		template<class TInstance>
		void getCoverArt(const QString &id, TInstance *instance, ImageCallback<TInstance> callback)
		{
			m_requestFactory
				.request("getCoverArt.view"
					, api::id = id
					, api::size = "64")
				.callback(instance, callback);
		}

		QNetworkReply *stream(const QString &id)
		{
			return m_requestFactory
				.request("stream.view"
					, api::id = id
					, api::format = "ogg"
					, api::maxBitRate = "320")
				.stream();
		}

	private:
		RequestFactory m_requestFactory;
};

#endif // SUBSONICADAPTER_H
