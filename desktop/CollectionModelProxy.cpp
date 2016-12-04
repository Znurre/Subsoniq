#include "CollectionModelProxy.h"

CollectionModelProxy::CollectionModelProxy()
{
	setSourceModel(&m_subject);
	setFilterRole(Qt::DisplayRole);
	setFilterCaseSensitivity(Qt::CaseInsensitive);
}
