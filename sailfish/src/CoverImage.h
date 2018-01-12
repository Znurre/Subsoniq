#ifndef COVERIMAGE_H
#define COVERIMAGE_H

#include <QQuickPaintedItem>

#include "SubsonicAdapter.h"

class CoverImage : public QQuickPaintedItem
{
	Q_OBJECT

	Q_PROPERTY(QString coverId READ coverId WRITE setCoverId NOTIFY coverIdChanged)
	Q_PROPERTY(QString size READ size WRITE setSize NOTIFY sizeChanged)

	Q_PROPERTY(bool isReady READ isReady NOTIFY isReadyChanged)

	public:
		CoverImage();

		QString size() const;
		void setSize(const QString &size);

		QString coverId() const;
		void setCoverId(const QString &id);

		bool isReady() const;

	private:
		void paint(QPainter *painter) override;
		void reply(const QImage &image);

		SubsonicAdapter m_adapter;

		QString m_coverId;
		QString m_size;

		QImage m_image;

		bool m_ready;

	signals:
		void coverIdChanged();
		void sizeChanged();
		void isReadyChanged();
};

#endif // COVERIMAGE_H
