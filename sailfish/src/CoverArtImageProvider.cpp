#include "CoverArtImageProvider.h"
#include "ImageResponseObject.h"
#include "SubsonicAdapter.h"

CoverArtImageProvider::CoverArtImageProvider()
	: QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage CoverArtImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
	Q_UNUSED(id);
	Q_UNUSED(size);
	Q_UNUSED(requestedSize);

//	const QUrl url(id, QUrl::TolerantMode);

//	const QString &imageId = url.path();
//	const QString &imageSize = url.query();

//	ImageResponseObject iro;
//	SubsonicAdapter adapter;

//	adapter.getCoverArt(imageId, imageSize, &iro, &ImageResponseObject::response);

//	return iro.image();

	return QImage();
}
