#ifndef ARTISTGROUPNODE_H
#define ARTISTGROUPNODE_H

#include <QJsonObject>
#include <QList>

#include "IArtistModelNode.h"

class ArtistGroupNode : public IArtistModelNode
{
	public:
		ArtistGroupNode(const QString &name, const QJsonObject &object);

		QString title() const override;
		QString id() const override;

		IArtistModelNode *childAt(int index) const override;

		int childCount() const override;

	private:
		QString m_name;
		QList<IArtistModelNode *> m_nodes;
};

#endif // ARTISTGROUPNODE_H
