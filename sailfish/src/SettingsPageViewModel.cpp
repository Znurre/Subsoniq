#include "SettingsPageViewModel.h"

SettingsPageViewModel::SettingsPageViewModel()
{
}

QString SettingsPageViewModel::serverUrl() const
{
	return m_settings.serverUrl();
}

void SettingsPageViewModel::setServerUrl(const QString &serverUrl)
{
	m_settings.setServerUrl(serverUrl);

	emit serverUrlChanged();
}

QString SettingsPageViewModel::username() const
{
	return m_settings.username();
}

void SettingsPageViewModel::setUsername(const QString &username)
{
	m_settings.setUsername(username);

	emit usernameChanged();
}

QString SettingsPageViewModel::password() const
{
	return m_settings.password();
}

void SettingsPageViewModel::setPassword(const QString &password)
{
	m_settings.setPassword(password);

	emit passwordChanged();
}

int SettingsPageViewModel::bitRate() const
{
	return m_settings.bitRate();
}

void SettingsPageViewModel::setBitRate(int bitRate)
{
	m_settings.setBitRate(bitRate);

	emit bitRateChanged();
}

bool SettingsPageViewModel::scrobble() const
{
	return m_settings.scrobble();
}

void SettingsPageViewModel::setScrobble(bool scrobble)
{
	m_settings.setScrobble(scrobble);

	emit scrobbleChanged();
}
