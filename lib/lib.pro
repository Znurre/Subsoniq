CONFIG += c++11 staticlib

QT += network multimedia

TEMPLATE = lib
TARGET = subsoniq

SOURCES += \
	Key.cpp \
	KeyValue.cpp \
	Player.cpp \
	Playlist.cpp \
	PlaylistIterator.cpp \
	PlaylistNode.cpp \
	PlaylistStream.cpp \
	QStringEx.cpp \
	QueryBuilder.cpp \
	Request.cpp \
	RequestFactory.cpp \
	Settings.cpp \
	Track.cpp \
	UrlBuilder.cpp \
    MetadataController.cpp \
    AudioBuffer.cpp \
    PlayerController.cpp \
    Scrobbler.cpp

HEADERS += \
	ImageResponseTransformer.h \
	IResponseTransformer.h \
	JsonResponseTransformer.h \
	Key.h \
	KeyValue.h \
	Player.h \
	Playlist.h \
	PlaylistIterator.h \
	PlaylistNode.h \
	PlaylistStream.h \
	QStringEx.h \
	QueryBuilder.h \
	Request.h \
	RequestFactory.h \
	ResponseCallback.h \
	ResponseTransformerBase.h \
	SenderInjector.h \
	Settings.h \
	SubsonicAdapter.h \
	Track.h \
	UrlBuilder.h \
    MetadataController.h \
    AudioBuffer.h \
    PlayerController.h \
    Scrobbler.h

