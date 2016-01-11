#ifndef COVERIMAGE_H
#define COVERIMAGE_H

#include <QQuickPaintedItem>

#include "SubsonicAdapter.h"

class CoverImage : public QQuickPaintedItem
{
	Q_OBJECT

	Q_PROPERTY(QString coverId READ coverId WRITE setCoverId NOTIFY coverIdChanged)
	Q_PROPERTY(bool isReady READ isReady NOTIFY isReadyChanged)

	public:
		CoverImage();

		QString coverId() const;
		void setCoverId(const QString &id);

		bool isReady() const;

	private:
		void paint(QPainter *painter) override;
		void reply(const QImage &image);

		SubsonicAdapter m_adapter;

		QString m_coverId;
		QImage m_image;

		bool m_ready;

	signals:
		void coverIdChanged();
		void isReadyChanged();
};

#endif // COVERIMAGE_H
