#ifndef ARTISTSPAGEVIEWMODEL_H
#define ARTISTSPAGEVIEWMODEL_H

#include <QObject>

class ArtistsPageViewModel : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QObject *selectedGroup READ selectedGroup WRITE setSelectedGroup NOTIFY selectedGroupChanged)

	public:
		ArtistsPageViewModel();

		QObject *selectedGroup() const;
		void setSelectedGroup(QObject *selectedGroup);

	private:
		QObject *m_selectedGroup;

	signals:
		void selectedGroupChanged();
};

#endif // ARTISTSPAGEVIEWMODEL_H
