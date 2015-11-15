#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include <QAbstractListModel>

class GroupModel : public QAbstractListModel
{
	Q_OBJECT

	Q_PROPERTY(QString role READ role WRITE setRole NOTIFY roleChanged)
	Q_PROPERTY(QObject *model READ model WRITE setModel NOTIFY modelChanged)

	public:
		GroupModel();

		QString role() const;
		void setRole(const QString &role);

		QObject *model() const;
		void setModel(QObject *model);

		int rowCount(const QModelIndex &parent) const override;

		QVariant data(const QModelIndex &index, int role) const override;

	private:
		void regenerate();

		QString m_role;
		QAbstractItemModel *m_model;
		QHash<QVariant, QObject *> m_groups;

	signals:
		void roleChanged();
		void modelChanged();
};

uint qHash(const QVariant & variant);

#endif // GROUPMODEL_H
