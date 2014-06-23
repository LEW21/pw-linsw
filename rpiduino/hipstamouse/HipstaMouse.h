#pragma once

#include <QtQml>
#include <atomic>
#include "pin.h"

class HipstaMouse: public QObject
{
	Q_OBJECT
	Q_PROPERTY(int displayedValue READ displayedValue WRITE setDisplayedValue NOTIFY displayedValueChanged)

	int value;

	pin pD0;
	pin pD1;
	pin pD2;
	pin pD3;

	pin pB0;
	pin pB1;
	pin pB2;

	std::ofstream D0;
	std::ofstream D1;
	std::ofstream D2;
	std::ofstream D3;

	int pipeToWorker;
	QFuture<void> worker;

private:
	void updateValue();

public:
	HipstaMouse();
	~HipstaMouse();

	int displayedValue() {return value;}
	void setDisplayedValue(int v) {value = v; updateValue(); emit displayedValueChanged();}

signals:
	void displayedValueChanged();
};

class HipstaMousePlugin : public QQmlExtensionPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
	void registerTypes(const char *uri)
	{
		Q_ASSERT(uri == QLatin1String("Hipsta"));
		qmlRegisterType<HipstaMouse>(uri, 1, 0, "Mouse");
	}
};
