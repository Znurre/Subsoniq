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
TARGET = subsoniq

CONFIG += sailfishapp c++11

QT += multimedia

SOURCES += src/sailfish.cpp \
    src/SettingsPageViewModel.cpp \
    src/ArtistsPageViewModel.cpp \
    src/ArtistsModel.cpp \
    src/CollectionNodeBase.cpp \
    src/CollectionArtistNode.cpp \
    src/GroupModel.cpp \
    src/ArtistGroupNode.cpp \
    src/ArtistGroupRow.cpp \
    src/ICollectionNodeResolver.cpp \
    src/CollectionAlbumNode.cpp \
    src/CollectionTrackNode.cpp \
    src/CollectionModel.cpp \
    src/CollectionRootNode.cpp \
    src/PlaylistModel.cpp \
    src/MainViewModel.cpp \
    src/CoverArtImageProvider.cpp \
    src/ImageResponseObject.cpp \
    src/MetadataController.cpp \
    src/ICollectionNodeProxy.cpp

OTHER_FILES += \
    qml/cover/CoverPage.qml \
    rpm/sailfish.changes.in \
    rpm/subsoniq.spec \
    rpm/sailfish.yaml \
    translations/*.ts \
    qml/pages/HubPage.qml \
    qml/pages/SettingsPage.qml \
    subsoniq.desktop \
    qml/subsoniq.qml \
    qml/pages/DirectoryPage.qml \
    qml/pages/ArtistTemplate.qml \
    qml/pages/AlbumTemplate.qml \
    qml/pages/TrackTemplate.qml \
    qml/pages/PlaylistPage.qml \
    qml/pages/MediaControls.qml \
    qml/pages/CollectionPage.qml

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/sailfish-de.ts

HEADERS += \
    src/SettingsPageViewModel.h \
    src/ArtistsPageViewModel.h \
    src/ArtistsModel.h \
    src/CollectionNodeBase.h \
    src/CollectionArtistNode.h \
    src/ICollectionNode.h \
    src/GroupModel.h \
    src/IArtistModelNode.h \
    src/ArtistGroupNode.h \
    src/ArtistGroupRow.h \
    src/ICollectionNodeResolver.h \
    src/CollectionAlbumNode.h \
    src/CollectionTrackNode.h \
    src/CollectionModel.h \
    src/CollectionRootNode.h \
    src/PlaylistModel.h \
    src/MainViewModel.h \
    src/CoverArtImageProvider.h \
    src/ImageResponseObject.h \
    src/MetadataController.h \
    src/ICollectionNodeProxy.h

LIBS += -L$$OUT_PWD/../lib/ -lsubsoniq

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib
