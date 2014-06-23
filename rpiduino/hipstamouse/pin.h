#pragma once

#include <string>
#include <fstream>
#include <iostream>

using std::string;
using std::ofstream;
using std::flush;

struct pin
{
	string id;

	pin(string id): id(id)
	{
		ofstream exp{"/sys/class/gpio/export"};
		exp << id << flush;
	}

	pin(const pin&) = delete;
	pin(pin&& other): id(move(other.id))
	{
		other.id = {};
	}

	~pin()
	{
		if (id.size())
		{
			ofstream unexp{"/sys/class/gpio/unexport"};
			unexp << id << flush;
		}
	}

	string dir() const
	{
		return "/sys/class/gpio/gpio" + id;
	}

	string enable_io(string state)
	{
		{
			ofstream f{dir() + "/direction"};
			f << state << flush;
		}

		if (state == "in")
		{
			ofstream f{dir() + "/edge"};
			f << "both" << flush;
		}

		return dir() + "/value";
	}
};
