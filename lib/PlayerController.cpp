#include "PlayerController.h"

void PlayerController::play()
{
	emit playRequested();
}

void PlayerController::playPause()
{
	emit playPauseRequested();
}

void PlayerController::setMedia(const QMediaContent &media, QIODevice *stream)
{
	emit setMediaRequested(media, stream);
}
