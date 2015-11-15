#ifndef ICOLLECTIONNODE
#define ICOLLECTIONNODE

#include <QString>
#include <QIcon>
#include <QList>
#include <QAbstractItemDelegate>

class Track;

class ICollectionNode : public QObject
{
	Q_OBJECT

	public:
		virtual ~ICollectionNode()
		{

		}

		virtual QIcon icon() const = 0;
		virtual QString title() const = 0;
		virtual QSize sizeHint() const = 0;

		virtual ICollectionNode *childAt(int index) const = 0;
		virtual ICollectionNode *parent() const = 0;

		virtual const Track *track() const = 0;

		virtual int row() const = 0;
		virtual int childCount() const = 0;

		virtual bool hasChildren() const = 0;
		virtual bool canFetchMore() const = 0;

		virtual void fetchMore() = 0;

	signals:
		void dataChanged(ICollectionNode *node);
};

#endif // ICOLLECTIONNODE

