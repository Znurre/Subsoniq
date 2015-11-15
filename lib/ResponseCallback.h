#ifndef RESPONSECALLBACK
#define RESPONSECALLBACK

#include <QJsonObject>
#include <QImage>

template<class TInstance, class TResult>
using ResponseCallback = void (TInstance::*)(const TResult &);

template<class TInstance>
using JsonCallback = ResponseCallback<TInstance, QJsonObject>;

template<class TInstance>
using ImageCallback = ResponseCallback<TInstance, QImage>;

#endif // RESPONSECALLBACK

