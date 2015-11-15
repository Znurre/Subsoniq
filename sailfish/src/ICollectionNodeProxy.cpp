#include "ICollectionNodeProxy.h"

ICollectionNodeProxy::ICollectionNodeProxy(ICollectionNode *subject)
	: m_subject(subject)
{

}

ICollectionNode *ICollectionNodeProxy::subject() const
{
	return m_subject;
}
