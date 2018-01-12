#ifndef STOREDPLAYLIST_H
#define STOREDPLAYLIST_H

#include <QObject>
#include <QJsonSerializer>

class CollectionTrackNode;

class StoredPlaylist : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(QString coverArt READ coverArt WRITE setCoverArt NOTIFY coverArtChanged)
	Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)

	Q_PROPERTY(QDateTime created READ created WRITE setCreated NOTIFY createdChanged)

	public:
		Q_INVOKABLE StoredPlaylist() = default;

		QString id() const;
		void setId(const QString &id);

		QString name() const;
		void setName(const QString &name);

		QString coverArt() const;
		void setCoverArt(const QString &coverArt);

		QString comment() const;
		void setComment(const QString &comment);

		QDateTime created() const;
		void setCreated(const QDateTime &created);

		QList<CollectionTrackNode *> tracks() const;
		void setTracks(QList<CollectionTrackNode *> tracks);

		Q_INVOKABLE QString getCreated() const;

		operator QString() const;

	private:
		QString m_id;
		QString m_name;
		QString m_coverArt;
		QString m_comment;

		QDateTime m_created;

		QList<CollectionTrackNode *> m_tracks;

	signals:
		void idChanged();
		void nameChanged();
		void coverArtChanged();
		void commentChanged();
		void createdChanged();
};

Q_DECLARE_METATYPE(StoredPlaylist *)
Q_DECLARE_METATYPE(Array<StoredPlaylist *>)

#endif // STOREDPLAYLIST_H
