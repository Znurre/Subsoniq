#include "PlayerController.h"

void PlayerController::play()
{
	emit playRequested();
}

void PlayerController::pause()
{
	emit pauseRequested();
}

void PlayerController::setMedia(const QMediaContent &media, QIODevice *stream)
{
	emit setMediaRequested(media, stream);
}
