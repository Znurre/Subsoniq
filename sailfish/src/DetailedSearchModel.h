#ifndef DETAILEDSEARCHMODEL_H
#define DETAILEDSEARCHMODEL_H

#include "SubsoniqModelBase.h"
#include "SubsonicAdapter.h"
#include "CollectionNodeBase.h"
#include "SearchModelBase.h"

class CollectionEndNode : public CollectionNodeBase
{
	public:
		QIcon icon() const override
		{
			return QIcon();
		}

		QString title() const override
		{
			return QString::null;
		}

		QString viewTemplate() const override
		{
			return QString::null;
		}

		QString id() const override
		{
			return QString::null;
		}

		QString grouping() const override
		{
			return QString::null;
		}
};

class DetailedSearchModel : public SearchModelBase
{
	Q_OBJECT

	Q_PROPERTY(QString query READ query WRITE setQuery NOTIFY queryChanged)
	Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)

	const QModelIndex NoParent;

	public:
		DetailedSearchModel();

		QString query() const;
		void setQuery(const QString &query);

		QString type() const;
		void setType(const QString &type);

		QModelIndex index(int row, int column, const QModelIndex &parent) const override;
		QVariant data(const QModelIndex &index, int role) const override;

		int rowCount(const QModelIndex &parent) const override;

		void fetch();
		void response(const QJsonObject &envelope);

	private:
		mutable DetailedSearchModel *m_self;
		mutable CollectionEndNode m_end;

		SubsonicAdapter m_adapter;

		QList<ICollectionNode *> m_nodes;

		QString m_query;
		QString m_type;

		bool m_canFetch;

	signals:
		void fetchMoreRequested();
		void queryChanged();
		void typeChanged();
};

#endif // DETAILEDSEARCHMODEL_H
