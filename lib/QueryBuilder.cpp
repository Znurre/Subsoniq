#include "QueryBuilder.h"

void QueryBuilder::setParameters(const QList<api::KeyValue> &values)
{
	for (const api::KeyValue &value : values)
	{
		m_parameters << value.asQueryParameter();
	}
}

QString QueryBuilder::build() const
{
	return m_parameters.join("&");
}

