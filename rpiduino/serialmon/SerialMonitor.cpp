#include "SerialMonitor.h"

#include <QSerialPort>
#include <QtConcurrent>
#include <thread>

SerialMonitor::SerialMonitor()
{
	QtConcurrent::run([this](){
		QSerialPort serial;

		forever
		{
			serial.setPortName("ttyACM0");
			if (serial.open(QIODevice::ReadWrite))
				break;

			serial.setPortName("ttyACM1");
			if (serial.open(QIODevice::ReadWrite))
				break;

			serial.setPortName("ttyACM2");
			if (serial.open(QIODevice::ReadWrite))
				break;

			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		serial.setBaudRate(9600);
		serial.setDataBits(QSerialPort::Data8);
		serial.setParity(QSerialPort::NoParity);
		serial.setStopBits(QSerialPort::OneStop);
		serial.setFlowControl(QSerialPort::NoFlowControl);

		auto firstMsg = true;

		auto buffer = QByteArray{};

		forever {
			if (!serial.waitForReadyRead(10000))
			{
				return;
			}

			buffer += serial.readAll();

			auto len = 0;
			auto msg = QByteArray{};
			while ((len = buffer.indexOf("\n\r\n")) != -1)
			{
				msg = buffer.left(len);
				buffer = buffer.mid(len+3);

				if (firstMsg)
				{
					firstMsg = false;
					// Ignore first message, it might be incomplete.
					msg = {};
				}
			}

			if (!msg.isEmpty())
			{
				auto l = QString{};
				auto t = QString{};

				auto vars = msg.split('\n');
				for (auto var : vars)
				{
					auto s = var.split(':');
					auto name = s[0];
					auto value = s[1].trimmed();

					if (name == "Oswietlenie")
						l = value;
					if (name == "Temperatura")
						t = value;
				}

				qDebug() << "0: " << l << t;
				QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection, Q_ARG(QString, l), Q_ARG(QString, t));
			}
		}
	});
}

void SerialMonitor::update(QString lu, QString te)
{
	l = lu;
	t = te;
	emit changed();
	qDebug() << "1: " << l << t;
}
