#include "MainViewModel.h"
#include "ICollectionNode.h"

MainViewModel::MainViewModel()
	: m_playlistModel(m_playlist)
	, m_player(m_playlist)
{
}

QObject *MainViewModel::playlistModel()
{
	return &m_playlistModel;
}

QObject *MainViewModel::playlist()
{
	return &m_playlist;
}

QObject *MainViewModel::player()
{
	return &m_player;
}
