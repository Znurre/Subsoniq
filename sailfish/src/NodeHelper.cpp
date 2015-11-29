#include "NodeHelper.h"
#include "ICollectionNode.h"
#include "QStringEx.h"

QString NodeHelper::getCoverUrl(ICollectionNode *node, const QString &size)
{
	const QString &id = node->id();
	const QString &url = QStringEx::format("image://cover/%1?%2", id, size);

	return url;
}
