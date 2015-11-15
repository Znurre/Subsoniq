#include "ArtistsPageViewModel.h"

ArtistsPageViewModel::ArtistsPageViewModel()
	: m_selectedGroup(nullptr)
{
}

QObject *ArtistsPageViewModel::selectedGroup() const
{
	return m_selectedGroup;
}

void ArtistsPageViewModel::setSelectedGroup(QObject *selectedGroup)
{
	m_selectedGroup = selectedGroup;

	emit selectedGroupChanged();
}
