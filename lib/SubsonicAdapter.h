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
			: m_requestFactory(parent, m_settings)
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
					, api::size = QStringLiteral("64"))
				.callback(instance, callback);
		}

		QNetworkReply *stream(const QString &id)
		{
			return m_requestFactory
				.request("stream.view"
					, api::id = id
					, api::maxBitRate = m_settings.bitRate()
					, api::format = QStringLiteral("ogg"))
				.stream();
		}

		void scrobble(const QString &id, bool submission)
		{
			m_requestFactory
				.request("scrobble.view"
					, api::id = id
					, api::submission = submission)
				.stream();
		}

	private:
		Settings m_settings;
		RequestFactory m_requestFactory;
};

#endif // SUBSONICADAPTER_H
