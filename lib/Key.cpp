#include "Key.h"

namespace api
{
	Key::Key(const char *name)
		: m_name(name)
	{

	}

	KeyValue Key::operator =(const QString &value) const
	{
		return KeyValue(m_name, value);
	}

	KeyValue Key::operator =(int value) const
	{
		const QString &string = QString::number(value);

		return KeyValue(m_name, string);
	}
}
