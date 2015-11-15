#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include <QStringList>

#include "KeyValue.h"

class QueryBuilder
{
	public:
		void setParameters(const QList<api::KeyValue> &values);

		QString build() const;

	private:
		QStringList m_parameters;
};

#endif // QUERYBUILDER_H
