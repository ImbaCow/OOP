#include "pch.h"
#include "ConsoleCalculator.h"

ConsoleCalculator::ConsoleCalculator(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

void ConsoleCalculator::Start()
{
	std::string commandLine;
	ShowCommands();

	while (!m_isProcessEnd && std::getline(m_input, commandLine))
	{
		try
		{
			HandleCommand(commandLine);
		}
		catch (const std::exception& e)
		{
			m_output << e.what() << std::endl
				   << "Enter 'help' to show commands list." << std::endl;
		}
	}
}

void ConsoleCalculator::HandleCommand(const std::string& commandLine)
{
	std::vector<std::string> commandArgs = SplitCommand(commandLine);
	CalcCommand calcCommand = StringToCommand(commandArgs[0]);

	switch (calcCommand)
	{
	case CalcCommand::Variable:
		VarCommand(commandArgs);
		break;
	case CalcCommand::Fn:
		FnCommand(commandArgs);
		break;
	case CalcCommand::Let:
		LetCommand(commandArgs);
		break;
	case CalcCommand::Print:
		PrintCommand(commandArgs);
		break;
	case CalcCommand::PrintVars:
		m_calc.PrintVars(m_output);
		break;
	case CalcCommand::PrintFns:
		m_calc.PrintFns(m_output);
		break;
	case CalcCommand::Help:
		ShowCommands();
		break;
	case CalcCommand::EndProcess:
		m_isProcessEnd = true;
		m_output << "Calculator end" << std::endl;
		break;
	default:
		break;
	}
}

CalcCommand ConsoleCalculator::StringToCommand(const std::string& commandString)
{
	CalcCommand result;
	if (commandString == "var")
	{
		result = CalcCommand::Variable;
	}
	else if (commandString == "fn")
	{
		result = CalcCommand::Fn;
	}
	else if (commandString == "let")
	{
		result = CalcCommand::Let;
	}
	else if (commandString == "print")
	{
		result = CalcCommand::Print;
	}
	else if (commandString == "printvars")
	{
		result = CalcCommand::PrintVars;
	}
	else if (commandString == "printfns")
	{
		result = CalcCommand::PrintFns;
	}
	else if (commandString == "stop")
	{
		result = CalcCommand::EndProcess;
	}
	else if (commandString == "help")
	{
		result = CalcCommand::Help;
	}
	else
	{
		throw std::invalid_argument("Unhandled command: '" + commandString + "' given.");
	}

	return result;
}

std::vector<std::string> ConsoleCalculator::SplitCommand(std::string commandString)
{
	std::vector<std::string> args;
	boost::trim_all(commandString);
	boost::split(args, commandString, [](char ch) {
		return ch == ' ';
	});
	return args;
}

void ConsoleCalculator::ShowCommands()
{
	m_output << "help - Show commands list" << std::endl
		   << "stop - Stop console calculator process" << std::endl
		   << "var <name1> - Define new variable" << std::endl
		   << "let <name1> = <double> - Initialize variable with double" << std::endl
		   << "let <name1> = <name2> - Initialize variable with another variable value" << std::endl
		   << "fn <name1> = <name2> - Initialize function with another value link" << std::endl
		   << "fn <name1> = <name2> <operation> <name3> - Initialize function with expression(+,-,*,/)" << std::endl
		   << "print <name1> - Show variable or function value" << std::endl
		   << "printvars - Show all variables value" << std::endl
		   << "printfns - Show all functions value" << std::endl;
}

void ConsoleCalculator::VarCommand(const std::vector<std::string>& commandArgs)
{
	if (commandArgs.size() < 2)
	{
		throw std::invalid_argument("Not enough arguments.");
	}
	std::string variableName = commandArgs[1];
	m_calc.Var(variableName);
}

void ConsoleCalculator::LetCommand(const std::vector<std::string>& commandArgs)
{
	if (commandArgs.size() < 4)
	{
		throw std::invalid_argument("Not enough arguments.");
	}
	if (commandArgs[2] != "=")
	{
		throw std::invalid_argument("Invalid command format.");
	}

	std::string varName(commandArgs[1]);
	std::string argument(commandArgs[3]);
	try
	{
		double value = boost::lexical_cast<double>(commandArgs[3]);
		m_calc.Let(varName, value);
	}
	catch (const boost::bad_lexical_cast&)
	{
		m_calc.Let(varName, argument);
	}
}

void ConsoleCalculator::FnCommand(const std::vector<std::string>& commandArgs)
{
	if (commandArgs.size() < 4)
	{
		throw std::invalid_argument("Not enough arguments.");
	}
	if (commandArgs[2] != "=")
	{
		throw std::invalid_argument("Invalid command format.");
	}

	if (commandArgs.size() < 6)
	{
		UnarFnCommand(commandArgs);
	}
	else
	{
		BinarFnCommand(commandArgs);
	}
}

void ConsoleCalculator::UnarFnCommand(const std::vector<std::string>& commandArgs)
{
	std::string fnName(commandArgs[1]);
	std::string argument(commandArgs[3]);

	m_calc.Fn(fnName, argument);
}

void ConsoleCalculator::BinarFnCommand(const std::vector<std::string>& commandArgs)
{
	std::string fnName(commandArgs[1]);
	std::string firstArgument(commandArgs[3]);
	std::string secondArgument(commandArgs[5]);
	BinarOperator op = StringToBinarOperator(commandArgs[4]);

	m_calc.Fn(fnName, firstArgument, secondArgument, op);
}

BinarOperator ConsoleCalculator::StringToBinarOperator(const std::string& operatorString)
{
	BinarOperator result;
	if (operatorString == "+")
	{
		result = BinarOperator::PLUS;
	}
	else if (operatorString == "-")
	{
		result = BinarOperator::SUB;
	}
	else if (operatorString == "*")
	{
		result = BinarOperator::MULT;
	}
	else if (operatorString == "/")
	{
		result = BinarOperator::DIV;
	}
	else
	{
		throw std::invalid_argument("Unhandled operator: '" + operatorString + "' given.");
	}

	return result;
}

void ConsoleCalculator::PrintCommand(const std::vector<std::string>& commandArgs)
{
	std::string variableName(commandArgs[1]);

	m_calc.Print(variableName, m_output);
}