#ifndef TYPEGROUPINGRESOLVER_H
#define TYPEGROUPINGRESOLVER_H

#include <QList>
#include <QString>

class ICollectionNode;

class IResolver
{
	public:
		virtual ~IResolver() = default;

		virtual bool canHandle(ICollectionNode *node) const = 0;
		virtual QString grouping() const = 0;
};

template<class TNode>
class Resolver : public IResolver
{
	public:
		Resolver(const QString &grouping)
			: m_grouping(grouping)
		{

		}

		bool canHandle(ICollectionNode *node) const override
		{
			return dynamic_cast<TNode *>(node);
		}

		QString grouping() const override
		{
			return m_grouping;
		}

	private:
		QString m_grouping;
};

class TypeGroupingResolver
{
	public:
		TypeGroupingResolver();
		~TypeGroupingResolver();

		QString resolve(ICollectionNode *node) const;

	private:
		QList<IResolver *> m_resolvers;
};

#endif // TYPEGROUPINGRESOLVER_H
