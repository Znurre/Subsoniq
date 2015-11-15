#include "Streamer.h"
#include "Track.h"

Streamer::Streamer()
	: m_reply(nullptr)
{
//	connect(&m_adapter, &SubsonicAdapter::finished, this, &Streamer::onFinished);
//	connect(&m_adapter, &SubsonicAdapter::readyRead, this, &Streamer::onReadyRead);
}

void Streamer::stream(const Track *track)
{
	if (m_reply)
	{
		m_reply->abort();
	}

//	m_reply = m_adapter
//		.request("stream.view"
//			, api::id = track->id()
//			, api::format = "raw"
//			, api::u = "Znurre"
//			, api::p = "gclinux"
//			, api::v = "1.12.0"
//			, api::c = "subsoniq");
}

void Streamer::onFinished(QNetworkReply *reply)
{
	reply->deleteLater();
}

void Streamer::onReadyRead(QNetworkReply *reply)
{
	const QByteArray &data = reply->readAll();

	emit dataAvailable(data);
}

