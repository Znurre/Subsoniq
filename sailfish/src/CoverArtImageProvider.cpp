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

	const QUrl url(id, QUrl::TolerantMode);

	const QString &i = url.path();
	const QString &s = url.query();

	qDebug() << i << s;

	ImageResponseObject iro;
	SubsonicAdapter adapter;

	adapter.getCoverArt(i, s, &iro, &ImageResponseObject::response);

	return iro.image();
}
