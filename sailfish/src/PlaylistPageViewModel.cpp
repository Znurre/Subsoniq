#include "PlaylistPageViewModel.h"

PlaylistPageViewModel::PlaylistPageViewModel()
	: m_editMode(false)
{

}

bool PlaylistPageViewModel::isEditMode() const
{
	return m_editMode;
}

void PlaylistPageViewModel::itemActivated(PlaylistNode *node)
{
	if (m_editMode)
	{
		m_editMode = false;

		emit isEditModeChanged();
	}
	else
	{
		emit playRequested(node);
	}
}

void PlaylistPageViewModel::enterEditMode()
{
	m_editMode = true;

	emit isEditModeChanged();
}

void PlaylistPageViewModel::leaveEditMode()
{
	m_editMode = false;

	emit isEditModeChanged();
}

void PlaylistPageViewModel::clear()
{
	m_editMode = false;

	emit isEditModeChanged();
	emit clearRequested();
}
