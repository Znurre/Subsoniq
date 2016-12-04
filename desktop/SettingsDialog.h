#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QLineEdit>

class SettingsDialog : public QDialog
{
	public:
		SettingsDialog();

	private:
		void onAccepted();

		QLineEdit *m_editServerAddress;
		QLineEdit *m_editUsername;
		QLineEdit *m_editPassword;
};

#endif // SETTINGSDIALOG_H
