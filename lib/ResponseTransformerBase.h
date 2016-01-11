#ifndef RESPONSETRANSFORMERBASE
#define RESPONSETRANSFORMERBASE

#include <QThread>
#include <QEventLoop>

#include "IResponseTransformer.h"
#include "ResponseCallback.h"

template<class TInstance, class TResult>
class ResponseTransformerBase : public IResponseTransformer
{
	public:
		ResponseTransformerBase(TInstance *instance, ResponseCallback<TInstance, TResult> callback, QNetworkReply *reply, QEventLoop *loop)
			: m_reply(reply)
			, m_loop(loop)
			, m_instance(instance)
			, m_callback(callback)
		{

		}

		virtual ~ResponseTransformerBase()
		{
			m_reply->deleteLater();
		}

		void handle() override
		{
			const TResult &value = transform(m_reply);

			(m_instance->*m_callback)(value);

			if (m_loop)
			{
				m_loop->quit();
			}

			delete this;
		}

	protected:
		virtual TResult transform(QNetworkReply *reply) const = 0;

	private:
		QNetworkReply *m_reply;
		QEventLoop *m_loop;

		TInstance *m_instance;
		ResponseCallback<TInstance, TResult> m_callback;
};

#endif // RESPONSETRANSFORMERBASE

