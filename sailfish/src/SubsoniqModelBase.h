#ifndef SUBSONIQMODELBASE_H
#define SUBSONIQMODELBASE_H

#include <QAbstractItemModel>

class ICollectionNode;

class SubsoniqModelBase : public QAbstractItemModel
{
	Q_OBJECT

	Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)

	Q_ENUMS(Status)

	public:
		enum Roles
		{
			ModelData = Qt::UserRole,
			Title = Qt::UserRole + 1,
			Icon = Qt::UserRole + 2,
			ViewTemplate = Qt::UserRole + 3,
			CoverUrl = Qt::UserRole + 4,
			Grouping = Qt::UserRole + 5,
			ModelIndex = Qt::UserRole + 6
		};

		enum Status
		{
			Loading,
			Finished
		};

		SubsoniqModelBase();

		QHash<int, QByteArray> roleNames() const override;
		QModelIndex parent(const QModelIndex &child) const override;

		int status() const;
		void setStatus(int status);

		int columnCount(const QModelIndex &parent) const override;

	private:
		int m_status;

	signals:
		void statusChanged();
};

#endif // SUBSONIQMODELBASE_H
