#ifndef FETCHMORENODE
#define FETCHMORENODE

#include "CollectionNodeBase.h"

template<class TBaseNode>
class FetchMoreNode : public CollectionNodeBase
{
	public:
		FetchMoreNode(const QString &query, const QString &type)
			: m_query(query)
			, m_type(type)
		{
			qDebug() << type << query;
		}

		QIcon icon() const override
		{
			return QIcon();
		}

		QString title() const override
		{
			return m_query;
		}

		QString viewTemplate() const override
		{
			return "FetchMoreTemplate.qml";
		}

		QString id() const override
		{
			return QString::null;
		}

		QString grouping() const override
		{
			return QString::null;
		}

		QString type() const override
		{
			return m_type;
		}

	private:
		QString m_query;
		QString m_type;
};

#endif // FETCHMORENODE

