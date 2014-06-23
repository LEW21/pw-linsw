#pragma once

#include <QtQml>
#include <atomic>

class SerialMonitor: public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString luminosity  READ luminosity  NOTIFY changed)
	Q_PROPERTY(QString temperature READ temperature NOTIFY changed)

	struct Private: public QObject
	{
		Private(QString lu, QString te): l(lu), t(te) {}

		QString l;
		QString t;
	};

	QString l;
	QString t;

public:
	SerialMonitor();

	QString luminosity() {return l;}
	QString temperature() {return t;}

private slots:
	void update(QString l, QString t);

signals:
	void changed();
};

class QExampleQmlPlugin : public QQmlExtensionPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
	void registerTypes(const char *uri)
	{
		Q_ASSERT(uri == QLatin1String("Synergy"));
		qmlRegisterType<SerialMonitor>(uri, 1, 0, "SerialMonitor");
	}
};
