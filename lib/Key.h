#ifndef KEY_H
#define KEY_H

#include "KeyValue.h"

namespace api
{
	class Key
	{
		public:
			Key(const char *name);

			KeyValue operator =(const QString &value) const;
			KeyValue operator =(int value) const;

		private:
			QString m_name;
	};

	const Key u = "u";
	const Key p = "p";
	const Key t = "t";
	const Key s = "s";
	const Key v = "v";
	const Key c = "c";
	const Key f = "f";
	const Key id = "id";
	const Key format = "format";
	const Key maxBitRate = "maxBitRate";
	const Key size = "size";
}

#endif // KEY_H
