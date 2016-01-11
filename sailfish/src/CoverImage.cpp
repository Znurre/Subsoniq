#include <QPainter>

#include "CoverImage.h"

CoverImage::CoverImage()
	: m_ready(false)
{

}

QString CoverImage::coverId() const
{
	return m_coverId;
}

void CoverImage::setCoverId(const QString &coverId)
{
	m_coverId = coverId;
	m_adapter.getCoverArt(coverId, "64", this, &CoverImage::reply);

	emit coverIdChanged();
}

bool CoverImage::isReady() const
{
	return m_ready;
}

void CoverImage::paint(QPainter *painter)
{
	const QRectF &rect = boundingRect();

	painter->drawImage(rect, m_image);
}

void CoverImage::reply(const QImage &image)
{
	m_image = image;
	m_ready = true;

	update();

	emit isReadyChanged();
}
