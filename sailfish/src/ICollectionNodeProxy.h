#ifndef ICOLLECTIONNODEPROXY_H
#define ICOLLECTIONNODEPROXY_H

#include <QObject>

class ICollectionNode;

class ICollectionNodeProxy : public QObject
{
	Q_OBJECT

	Q_PROPERTY(ICollectionNode *subject READ subject CONSTANT)

	public:
		ICollectionNodeProxy(ICollectionNode *subject);

		ICollectionNode *subject() const;

	private:
		ICollectionNode *m_subject;
};

#endif // ICOLLECTIONNODEPROXY_H
