#ifndef SEARCHMODELBASE_H
#define SEARCHMODELBASE_H

#include "SubsoniqModelBase.h"
#include "TypeGroupingResolver.h"

const int LIMIT = 20;

class SearchModelBase : public SubsoniqModelBase
{
	public:
		SearchModelBase();

		QVariant data(const QModelIndex &index, int role) const override;

	private:
		TypeGroupingResolver m_typeGroupingResolver;
};

#endif // SEARCHMODELBASE_H
