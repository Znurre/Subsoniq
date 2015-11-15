#ifndef ARTISTGROUPROW_H
#define ARTISTGROUPROW_H

#include <QList>

#include "IArtistModelNode.h"

class ArtistGroupRow : public IArtistModelNode
{
	public:
		ArtistGroupRow(int columns, int offset, const QList<IArtistModelNode *> &nodes);

		QString title() const override;
		QString id() const override;

		IArtistModelNode *childAt(int index) const override;

		int childCount() const override;

	private:
		QList<IArtistModelNode *> m_nodes;

		int m_columns;
		int m_offset;
};

#endif // ARTISTGROUPROW_H
