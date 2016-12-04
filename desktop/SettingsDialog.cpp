#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>

#include "SettingsDialog.h"
#include "Settings.h"

SettingsDialog::SettingsDialog()
{
	m_editServerAddress = new QLineEdit();
	m_editUsername = new QLineEdit();

	m_editPassword = new QLineEdit();
	m_editPassword->setEchoMode(QLineEdit::Password);

	QFormLayout *layout = new QFormLayout(this);

	layout->addRow("Server", m_editServerAddress);
	layout->addRow("Username", m_editUsername);
	layout->addRow("Password", m_editPassword);

	QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

	layout->addRow(buttons);

	connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

	connect(this, &QDialog::accepted, this, &SettingsDialog::onAccepted);
}

void SettingsDialog::onAccepted()
{
	const QString &serverUrl = m_editServerAddress->text();
	const QString &username = m_editUsername->text();
	const QString &password = m_editPassword->text();

	Settings settings;

	settings.setServerUrl(serverUrl);
	settings.setUsername(username);
	settings.setPassword(password);
}
