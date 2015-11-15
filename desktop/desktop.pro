CONFIG += c++11

QT += widgets network multimedia

TARGET = subsoniq

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    CollectionBrowser.cpp \
    PlaylistWidget.cpp \
    CollectionModel.cpp \
    CollectionRootNode.cpp \
    CollectionArtistNode.cpp \
    CollectionAlbumNode.cpp \
    CollectionItemDelegate.cpp \
    CollectionAlbumItemDelegate.cpp \
    CollectionArtistItemDelegate.cpp \
    ItemDelegateBase.cpp \
    CollectionNodeBase.cpp \
    CollectionTrackNode.cpp \
    ICollectionNodeResolver.cpp \
	PlaylistModel.cpp

HEADERS += \
    MainWindow.h \
    CollectionBrowser.h \
    PlaylistWidget.h \
    CollectionModel.h \
    CollectionRootNode.h \
    ICollectionNode.h \
    CollectionArtistNode.h \
    CollectionAlbumNode.h \
    CollectionItemDelegate.h \
    CollectionAlbumItemDelegate.h \
    CollectionArtistItemDelegate.h \
    ItemDelegateBase.h \
    CollectionNodeBase.h \
    CollectionTrackNode.h \
    ICollectionNodeResolver.h \
	PlaylistModel.h

LIBS += -L$$OUT_PWD/../lib/ -lsubsoniq

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib
