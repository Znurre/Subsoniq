#include "ImageResponseObject.h"

void ImageResponseObject::response(const QImage &image)
{
	m_image = image;
}

QImage ImageResponseObject::image() const
{
	return m_image;
}
