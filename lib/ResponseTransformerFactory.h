#ifndef RESPONSETRANSFORMERFACTORY
#define RESPONSETRANSFORMERFACTORY

#include "IResponseTransformer.h"
#include "ResponseTransformerBase.h"
#include "ResponseCallback.h"
#include "JsonResponseTransformer.h"
#include "ImageResponseTransformer.h"

#include <QJsonDocument>
#include <QWaitCondition>

class ResponseTransformerFactory
{
	public:
		template<class TInstance>
		IResponseTransformer &create(TInstance *instance, JsonCallback<TInstance> callback, QNetworkReply *reply, QEventLoop *loop)
		{
			return *new JsonResponseTransformer<TInstance>(instance, callback, reply, loop);
		}

		template<class TInstance>
		IResponseTransformer &create(TInstance *instance, ImageCallback<TInstance> callback, QNetworkReply *reply, QEventLoop *loop)
		{
			return *new ImageResponseTransformer<TInstance>(instance, callback, reply, loop);
		}
};

#endif // RESPONSETRANSFORMERFACTORY

