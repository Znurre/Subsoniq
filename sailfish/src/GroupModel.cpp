#include <QSet>
#include <QDebug>

#include "GroupModel.h"

GroupModel::GroupModel()
	: m_model(nullptr)
{

}

QString GroupModel::role() const
{
	return m_role;
}

void GroupModel::setRole(const QString &role)
{
	m_role = role;

	emit roleChanged();
}

QObject *GroupModel::model() const
{
	return m_model;
}

void GroupModel::setModel(QObject *model)
{
	m_model = qobject_cast<QAbstractItemModel *>(model);

	if (m_model)
	{
		connect(m_model, &QAbstractItemModel::layoutChanged, this, &QAbstractItemModel::layoutChanged);
	}

	emit modelChanged();
}

int GroupModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	if (m_model)
	{
		const QHash<int, QByteArray> &roles = m_model->roleNames();
		const QByteArray &value = m_role.toLatin1();

		const int mappedRole = roles.key(value);
		const int rowCount = m_model->rowCount();

		QSet<QString> groups;

		for (int i = 0; i < rowCount; i++)
		{
			const QModelIndex &index = m_model->index(i, 0);
			const QVariant &variant = m_model->data(index, mappedRole);

			groups << variant.toString();
		}

		qDebug() << groups.count();

		return groups.count();
	}

	return 0;
}

QVariant GroupModel::data(const QModelIndex &index, int role) const
{
	Q_UNUSED(index);
	Q_UNUSED(role);

//	if (m_model)
//	{
//		const QHash<int, QByteArray> &roles = m_model->roleNames();
//		const QByteArray &value = m_role.toLatin1();

//		const int mappedRole = roles.key(value);

//		m_model->data()
//	}

	return QVariant();
}

void GroupModel::regenerate()
{
	m_groups.clear();

	if (m_model)
	{
		const QHash<int, QByteArray> &roles = m_model->roleNames();
		const QByteArray &value = m_role.toLatin1();

		const int mappedRole = roles.key(value);
		const int rowCount = m_model->rowCount();

		QSet<QString> groups;

		for (int i = 0; i < rowCount; i++)
		{
			const QModelIndex &index = m_model->index(i, 0);
			const QVariant &variant = m_model->data(index, mappedRole);

//			m_groups[variant]
		}

		qDebug() << groups.count();

//		return groups.count();
	}

	emit layoutChanged();
}

uint qHash(const QVariant &variant)
{
	const QVariant::Type type = variant.type();

	switch (type)
	{
		case QVariant::Int:
		{
			const int value = variant.toInt();

			return qHash(value);
		}

		case QVariant::Double:
		case QVariant::Bool:
		case QVariant::UInt:
		{
			const uint value = variant.toUInt();

			return qHash(value);
		}

		case QVariant::LongLong:
		case QVariant::ULongLong:
		{
			const qlonglong value = variant.toLongLong();

			return qHash(value);
		}

		case QVariant::Char:
		{
			const QChar &character = variant.toChar();

			return qHash(character);
		}

		case QVariant::ByteArray:
		{
			const QByteArray &array = variant.toByteArray();

			return qHash(array);
		}

		case QVariant::String:
		case QVariant::StringList:
		case QVariant::Date:
		case QVariant::Time:
		case QVariant::DateTime:
		case QVariant::Url:
		case QVariant::Locale:
		case QVariant::RegExp:
		{
			const QString &string = variant.toString();

			return qHash(string);
		}

		default:
		{
			return -1;
		}
	}

	return -1;
}
