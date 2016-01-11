#ifndef ICOLLECTIONNODE
#define ICOLLECTIONNODE

#include <QString>
#include <QIcon>
#include <QList>

class Track;

class ICollectionNode : public QObject
{
	Q_OBJECT

	public:
		virtual ~ICollectionNode() = default;

		virtual QIcon icon() const = 0;

		virtual QString title() const = 0;
		virtual QString viewTemplate() const = 0;
		virtual QString id() const = 0;
		virtual QString grouping() const = 0;

		virtual ICollectionNode *childAt(int index) const = 0;

		virtual Track *track() = 0;

		virtual int childCount() const = 0;

		virtual bool hasChildren() const = 0;
		virtual bool canFetchMore() const = 0;

		virtual void fetchMore() = 0;

		operator QString() const
		{
			return id();
		}
};

#endif // ICOLLECTIONNODE

