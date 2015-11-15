#ifndef COVERARTIMAGEPROVIDER_H
#define COVERARTIMAGEPROVIDER_H

#include <QQuickImageProvider>

class CoverArtImageProvider : public QQuickImageProvider
{
	public:
		CoverArtImageProvider();

		QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

	private:
		void response(const QImage &image);
};

#endif // COVERARTIMAGEPROVIDER_H
