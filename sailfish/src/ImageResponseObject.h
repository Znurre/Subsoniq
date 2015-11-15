#ifndef IMAGERESPONSEOBJECT_H
#define IMAGERESPONSEOBJECT_H

#include <QImage>

class ImageResponseObject
{
	public:
		void response(const QImage &image);

		QImage image() const;

	private:
		QImage m_image;
};

#endif // IMAGERESPONSEOBJECT_H
