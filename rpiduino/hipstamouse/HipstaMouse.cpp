#include "HipstaMouse.h"

#include <QGuiApplication>
#include <QMouseEvent>
#include <QWindow>
#include <QtConcurrent>
#include <thread>
#include <iostream>
#include <thread>
#include <signal.h>
#include <cstring>
#include <poll.h>
#include "pin.h"
#include <unistd.h>

using namespace std;
using namespace std::chrono;

/*
auto pB = pin("17");
auto pW = pin("18");
auto pG = pin("23");
auto pR = pin("24");

auto pB0 = pin("10");
auto pB1 = pin("27"); // not 21!
auto pB2 = pin("22");
*/

HipstaMouse::HipstaMouse()
	: pD0("17"), pD1("18"), pD2("23"), pD3("24"), pB0("10"), pB1("27"), pB2("22"), D0(pD0.enable_io("low")), D1(pD1.enable_io("low")), D2(pD2.enable_io("low")), D3(pD3.enable_io("low"))
{
	int fildes[2];
	pipe(fildes);

	pipeToWorker = fildes[0];
	int pipeToMain = fildes[1];

	worker = QtConcurrent::run([this, pipeToMain](){
		auto B0 = fopen(pB0.enable_io("in").c_str(), "rb");
		if (!B0)
			perror("fopen");

		auto B1 = fopen(pB1.enable_io("in").c_str(), "rb");
		if (!B1)
			perror("fopen");

		auto B2 = fopen(pB2.enable_io("in").c_str(), "rb");
		if (!B2)
			perror("fopen");

		char oldleft  = '1';
		char oldmid   = '1';
		char oldright = '1';

		forever
		{
			pollfd buttons[4];
			buttons[0].fd = fileno(B0);
			buttons[0].events = POLLPRI | POLLERR;

			buttons[1].fd = fileno(B1);
			buttons[1].events = POLLPRI | POLLERR;

			buttons[2].fd = fileno(B2);
			buttons[2].events = POLLPRI | POLLERR;

			buttons[3].fd = pipeToMain;
			buttons[3].events = POLLIN | POLLPRI | POLLERR;

			fseek(B0, 0, SEEK_SET);
			fseek(B1, 0, SEEK_SET);
			fseek(B2, 0, SEEK_SET);

			auto pollres = poll(buttons, 4, -1);
			if (pollres < 0)
				perror("poll");
			else if (pollres == 0)
				cout << "poll timeout" << endl; //impossible

			if (buttons[3].revents)
				break;

			char left  = fgetc(B0);
			char mid   = fgetc(B1);
			char right = fgetc(B2);

			auto pressedButtons = (left == '0' ? Qt::LeftButton : Qt::NoButton) | (mid == '0' ? Qt::MidButton : Qt::NoButton) | (right == '0' ? Qt::RightButton : Qt::NoButton);

			if (mid != oldmid)
			{
				auto event = (mid == '0') ? QEvent::MouseButtonPress : QEvent::MouseButtonRelease;
				QCoreApplication::postEvent(QGuiApplication::focusWindow(), new QMouseEvent(event, QPointF{0, 0}, Qt::MidButton, pressedButtons, Qt::NoModifier));
			}

			if (left != oldleft)
			{
				auto event = (left == '0') ? QEvent::MouseButtonPress : QEvent::MouseButtonRelease;
				QCoreApplication::postEvent(QGuiApplication::focusWindow(), new QMouseEvent(event, QPointF{0, 0}, Qt::LeftButton, pressedButtons, Qt::NoModifier));
			}

			if (right != oldright)
			{
				auto event = (right == '0') ? QEvent::MouseButtonPress : QEvent::MouseButtonRelease;
				QCoreApplication::postEvent(QGuiApplication::focusWindow(), new QMouseEvent(event, QPointF{0, 0}, Qt::RightButton, pressedButtons, Qt::NoModifier));
			}

			oldleft  = left;
			oldmid   = mid;
			oldright = right;

			char buffer[1024];
			fread(buffer, 1024, 1024, B0);
			fread(buffer, 1024, 1024, B1);
			fread(buffer, 1024, 1024, B2);

			this_thread::sleep_for(milliseconds(10));
		}
	});
}

void HipstaMouse::updateValue()
{
	D0 << (value & 1 ? "1" : "0") << flush;
	D1 << (value & 2 ? "1" : "0") << flush;
	D2 << (value & 4 ? "1" : "0") << flush;
	D3 << (value & 8 ? "1" : "0") << flush;
}

HipstaMouse::~HipstaMouse()
{
	qDebug("~HipstaMouse");

	write(pipeToWorker, "Q", 1);

	worker.waitForFinished();

	D0 << "0" << flush;
	D1 << "0" << flush;
	D2 << "0" << flush;
	D3 << "0" << flush;
}
