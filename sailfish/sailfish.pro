# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-subsoniq

CONFIG += sailfishapp c++11

QT += multimedia

SOURCES += src/sailfish.cpp \
    src/SettingsPageViewModel.cpp \
    src/CollectionNodeBase.cpp \
    src/CollectionArtistNode.cpp \
    src/ICollectionNodeResolver.cpp \
    src/CollectionAlbumNode.cpp \
    src/CollectionTrackNode.cpp \
    src/CollectionModel.cpp \
    src/CollectionRootNode.cpp \
    src/PlaylistModel.cpp \
    src/MainViewModel.cpp \
    src/CoverArtImageProvider.cpp \
    src/ImageResponseObject.cpp \
    src/ICollectionNodeProxy.cpp \
    src/MediaControlsViewModel.cpp \
    src/HighlightsModel.cpp \
    src/NodeHelper.cpp \
    src/CollectionModelProxy.cpp \
    src/SearchModel.cpp \
    src/TypeGroupingResolver.cpp

OTHER_FILES += \
    qml/cover/CoverPage.qml \
    rpm/harbour-subsoniq.spec \
    translations/*.ts \
    qml/pages/SettingsPage.qml \
    qml/subsoniq.qml \
    qml/pages/ArtistTemplate.qml \
    qml/pages/AlbumTemplate.qml \
    qml/pages/TrackTemplate.qml \
    qml/pages/PlaylistPage.qml \
    qml/pages/MediaControls.qml \
    qml/pages/CollectionPage.qml \
    rpm/harbour-subsoniq.changes.in \
    rpm/harbour-subsoniq.yaml \
    harbour-subsoniq.desktop \
    qml/pages/AlbumPage.qml \
    qml/pages/SubsoniqPage.qml \
    qml/pages/SubsoniqMenuItem.qml \
    qml/pages/SearchPage.qml \
    qml/pages/ArtistsPage.qml

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/sailfish-de.ts

HEADERS += \
    src/SettingsPageViewModel.h \
    src/CollectionNodeBase.h \
    src/CollectionArtistNode.h \
    src/ICollectionNode.h \
    src/IArtistModelNode.h \
    src/ICollectionNodeResolver.h \
    src/CollectionAlbumNode.h \
    src/CollectionTrackNode.h \
    src/CollectionModel.h \
    src/CollectionRootNode.h \
    src/PlaylistModel.h \
    src/MainViewModel.h \
    src/CoverArtImageProvider.h \
    src/ImageResponseObject.h \
    src/ICollectionNodeProxy.h \
    src/MediaControlsViewModel.h \
    src/HighlightsModel.h \
    src/NodeHelper.h \
    src/CollectionModelProxy.h \
    src/ICollectionModel.h \
    src/SearchModel.h \
    src/TypeGroupingResolver.h

resources.files = icon-s-album.png icon-s-playlist.png
resources.path = /usr/share/$${TARGET}

INSTALLS += resources

LIBS += -L$$OUT_PWD/../lib/ -lsubsoniq

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib
