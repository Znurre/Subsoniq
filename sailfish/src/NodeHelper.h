#ifndef NODEHELPER_H
#define NODEHELPER_H

#include <QString>

class ICollectionNode;

class NodeHelper
{
	public:
		static QString getCoverUrl(ICollectionNode *node, const QString &size);
};

#endif // NODEHELPER_H
