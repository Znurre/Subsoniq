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
		SubsonicAdapter &getIndexes(TInstance *instance, JsonCallback<TInstance> callback)
		{
			m_requestFactory
				.request("getIndexes.view")
				.callback(instance, callback);

			return *this;
		}

		template<class TInstance>
		SubsonicAdapter &getMusicDirectory(const QString &id, TInstance *instance, JsonCallback<TInstance> callback)
		{
			m_requestFactory
				.request("getMusicDirectory.view"
					, api::id = id)
				.callback(instance, callback);

			return *this;
		}

		template<class TInstance>
		SubsonicAdapter &getCoverArt(const QString &id, const QString &size, TInstance *instance, ImageCallback<TInstance> callback)
		{
			m_requestFactory
				.request("getCoverArt.view"
					, api::id = id
					, api::size = size)
				.asyncCallback(instance, callback);

			return *this;
		}

		template<class TInstance>
		SubsonicAdapter &getAlbumList(const QString &type, TInstance *instance, JsonCallback<TInstance> callback)
		{
			m_requestFactory
				.request("getAlbumList.view"
					, api::type = type
					, api::size = QStringLiteral("9"))
				.callback(instance, callback);

			return *this;
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

		SubsonicAdapter &scrobble(const QString &id, bool submission)
		{
			m_requestFactory
				.request("scrobble.view"
					, api::id = id
					, api::submission = submission)
				.stream();

			return *this;
		}

		template<class TInstance, class TMethodInstance>
		SubsonicAdapter &search2(const QString &query, int limit, int offset, TInstance *instance, JsonCallback<TMethodInstance> callback)
		{
			m_requestFactory
				.request("search2.view"
					, api::query = query
					, api::artistCount = limit
					, api::artistOffset = offset
					, api::albumCount = limit
					, api::albumOffset = offset
					, api::songCount = limit
					, api::songOffset = offset)
				.asyncCallback(instance, callback);

			return *this;
		}

	private:
		Settings m_settings;
		RequestFactory m_requestFactory;
};

#endif // SUBSONICADAPTER_H
