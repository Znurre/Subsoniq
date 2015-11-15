#ifndef SENDERINJECTOR
#define SENDERINJECTOR

#include <QObject>

template<class TSender, class TInstance>
using SenderCallback = void (TInstance::*)(TSender *);

class ISenderInjector : public QObject
{
	public:
		virtual void invoke() = 0;
};

struct SenderInjector
{
	template<class TSender, class TInstance>
	class Implementation : public ISenderInjector
	{
		public:
			Implementation(TSender *sender, TInstance *instance, SenderCallback<TSender, TInstance> callback)
				: m_sender(sender)
				, m_instance(instance)
				, m_callback(callback)
			{
				connect(sender, &QObject::destroyed, this, &QObject::deleteLater);
			}

			void invoke()
			{
				(m_instance->*m_callback)(m_sender);
			}

		private:
			TSender *m_sender;
			TInstance *m_instance;

			SenderCallback<TSender, TInstance> m_callback;
	};

	template<class TSender, class TInstance>
	static Implementation<TSender, TInstance> *create(TSender *sender, TInstance *instance, SenderCallback<TSender, TInstance> callback)
	{
		return new Implementation<TSender, TInstance>(sender, instance, callback);
	}
};

#endif // SENDERINJECTOR

