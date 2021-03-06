#include "pch.h"
#include "CTVSet.h"

using namespace std;

enum ConsoleCommands
{
	TurnOn,
	TurnOff,
	Info,
	SelectPreviousChannel,
	ExitCommand,
	SelectChannel,
	SetChannelName,
	DeleteChannelName,
	ConsoleInfo
};

string CommandToString(ConsoleCommands command)
{
	switch (command)
	{
	case TurnOn: return "TurnOn";
	case TurnOff: return "TurnOff";
	case Info: return "Info";
	case SelectPreviousChannel: return "SelectPreviousChannel";
	case ExitCommand: return "Exit";
	case SelectChannel: return "SelectChannel";
	case SetChannelName: return "SetChannelName";
	case DeleteChannelName: return "DeleteChannelName";
	case ConsoleInfo: return "ConsoleInfo";
	default: throw logic_error("Unexpected command number");
	}
}

bool IsNumeric(const string & str)
{
	return all_of(str.begin(), str.end(), isdigit);
}

void GetConsoleInfo()
{
	cout << "Turn on tv - 'TurnOn'" << endl;
	cout << "Turn off tv - 'TurnOff'" << endl;
	cout << "Select channel by number - 'SelectChannel <number>'" << endl;
	cout << "Select channel by string - 'SelectChannel <string>'" << endl;
	cout << "Select previous channel - 'SelectPreviousChannel'" << endl;
	cout << "Set channel name - 'SetChannelName <channel number> <new name>'" << endl;
	cout << "Delete channel name - 'DeleteChannelName <name for delete>'" << endl;
	cout << "Get tv info - 'Info'" << endl;
	cout << "Get console commands - 'ConsoleInfo'" << endl;
	cout << "Exit from program - 'Exit'" << endl;
}

bool HandleCommand(CTVSet & tv, const string & command_line)
{
	stringstream sstream(command_line);
	string command;
	sstream >> command;
	if (command == CommandToString(TurnOn))
	{
		tv.TurnOn();
	}
	else if (command == CommandToString(TurnOff))
	{
		tv.TurnOff();
	}
	else if (command == CommandToString(Info))
	{
		tv.Info();
	}
	else if (command == CommandToString(ConsoleInfo))
	{
		GetConsoleInfo();
	}
	else if (command == CommandToString(SelectPreviousChannel))
	{
		tv.SelectPreviousChannel();
	}
	else if (command == CommandToString(ExitCommand))
	{
		return false;
	}
	else if (command == CommandToString(SelectChannel))
	{
		string input;
		sstream.get();
		getline(sstream, input);

		if (IsNumeric(input))
		{
			tv.SelectChannel(stoi(input));
		}
		else
		{
			tv.SelectChannel(input);
		}
	}
	else if (command == CommandToString(DeleteChannelName))
	{
		string input;
		sstream.get();
		getline(sstream, input);
		tv.DeleteChannelName(input);
	}
	else if (command == CommandToString(SetChannelName))
	{
		unsigned channelNumber;
		string newName;
		sstream >> channelNumber;
		sstream.get();
		getline(sstream, newName);
		tv.SetChannelName(channelNumber, newName);
	}
	else
	{
		cout << "Unexpected command" << endl;
	}

	return true;
}

int main()
{
	CTVSet tv;
	string command;
	bool needToContine = true;
	GetConsoleInfo();

	while (needToContine)
	{
		getline(cin, command);
		try
		{
			needToContine = HandleCommand(tv, command);
		}
		catch (const exception & ex)
		{
			cerr << ex.what() << endl;
		}
	}
}
