#include "MainWindow.h"
#include "SubsonicAdapter.h"
#include "Key.h"

#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

int main(int argc, char **argv)
{
	QApplication application(argc, argv);

	MainWindow window;
	window.resize(960, 720);
	window.show();

//	QNetworkAccessManager network;

//	QString url = "http://music.kwarf.com/rest/ping.view?u=Znurre&p=gclinux&v=1.12.0&c=subsoniq&f=json";
//	QNetworkRequest request(url);

//	QNetworkReply *reply = network.get(request);

//	qDebug() << reply->readAll();

	return application.exec();
}
