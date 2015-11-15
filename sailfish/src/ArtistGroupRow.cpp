#include "ArtistGroupRow.h"

ArtistGroupRow::ArtistGroupRow(int columns, int offset, const QList<IArtistModelNode *> &nodes)
	: m_nodes(nodes)
	, m_columns(columns)
	, m_offset(offset)
{

}

QString ArtistGroupRow::title() const
{
	return QString::null;
}

QString ArtistGroupRow::id() const
{
	return QString::null;
}

IArtistModelNode *ArtistGroupRow::childAt(int index) const
{
	return m_nodes[m_offset * m_columns + index];
}

int ArtistGroupRow::childCount() const
{
	return m_columns;
}
