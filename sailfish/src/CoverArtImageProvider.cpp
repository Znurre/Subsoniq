#include "CoverArtImageProvider.h"
#include "ImageResponseObject.h"
#include "SubsonicAdapter.h"

CoverArtImageProvider::CoverArtImageProvider()
	: QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage CoverArtImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
	Q_UNUSED(size);
	Q_UNUSED(requestedSize);

	ImageResponseObject iro;
	SubsonicAdapter adapter;

	adapter.getCoverArt(id, &iro, &ImageResponseObject::response);

	return iro.image();
}
