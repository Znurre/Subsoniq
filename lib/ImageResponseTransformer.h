#ifndef IMAGERESPONSETRANSFORMER_H
#define IMAGERESPONSETRANSFORMER_H

#include <QImage>

#include "ResponseTransformerBase.h"

template<class TInstance>
class ImageResponseTransformer : public ResponseTransformerBase<TInstance, QImage>
{
	public:
		ImageResponseTransformer(TInstance *instance, ImageCallback<TInstance> callback, QNetworkReply *reply, QEventLoop &loop)
			: ResponseTransformerBase<TInstance, QImage>(instance, callback, reply, loop)
		{

		}

		QImage transform(QNetworkReply *reply) const override
		{
			const QByteArray &data = reply->readAll();
			const QImage &image = QImage::fromData(data);

			return image;
		}
};

#endif // IMAGERESPONSETRANSFORMER_H
