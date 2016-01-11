#ifndef JSONRESPONSETRANSFORMER_H
#define JSONRESPONSETRANSFORMER_H

#include <QJsonObject>
#include <QJsonDocument>

#include "ResponseTransformerBase.h"

template<class TInstance>
class JsonResponseTransformer : public ResponseTransformerBase<TInstance, QJsonObject>
{
	public:
		JsonResponseTransformer(TInstance *instance, JsonCallback<TInstance> callback, QNetworkReply *reply, QEventLoop *loop)
			: ResponseTransformerBase<TInstance, QJsonObject>(instance, callback, reply, loop)
		{

		}

		QJsonObject transform(QNetworkReply *reply) const override
		{
			const QByteArray &json = reply->readAll();
			const QJsonDocument &document = QJsonDocument::fromJson(json);

			const QJsonObject &root = document
				.object();

			const QJsonObject &envelope = root
				.value("subsonic-response")
				.toObject();

			const QString &status = envelope
				.value("status")
				.toString();

			if (status == "ok")
			{
				return envelope;
			}

			qDebug() << "ERROR";
			qDebug() << envelope;

			return QJsonObject();
		}
};

#endif // JSONRESPONSETRANSFORMER_H
