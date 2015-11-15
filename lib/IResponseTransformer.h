#ifndef IRESPONSETRANSFORMER
#define IRESPONSETRANSFORMER

#include <QNetworkReply>
#include <QObject>

class IResponseTransformer : public QObject
{
	Q_OBJECT

	public:
		template <typename Func1, typename Func2>
		inline QMetaObject::Connection connect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal, Func2 slot)
		{
			return QObject::connect(sender, signal, this, slot, Qt::QueuedConnection);
		}

	public slots:
		virtual void handle() = 0;
};

#endif // IRESPONSETRANSFORMER

