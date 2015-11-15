#ifndef IARTISTMODELNODE_H
#define IARTISTMODELNODE_H

#include <QString>

class IArtistModelNode
{
	public:
		virtual QString title() const = 0;
		virtual QString id() const = 0;
		virtual QString grouping() const = 0;
		virtual QString viewTemplate() const = 0;

		virtual IArtistModelNode *childAt(int index) const = 0;

		virtual int childCount() const = 0;
};

#endif // IARTISTMODELNODE_H
