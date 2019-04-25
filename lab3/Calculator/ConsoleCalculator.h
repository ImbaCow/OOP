#pragma once
#include "Calculator.h"

enum CalcCommand
{
	Variable,
	Let,
	Fn,
	Print,
	PrintVars,
	PrintFns,
	Help,
	EndProcess
};

class ConsoleCalculator
{
public:
	ConsoleCalculator(std::istream& input, std::ostream& output);
	void Start();

private:
	std::istream& m_input;
	std::ostream& m_output;

	Calculator m_calc;
	bool m_isProcessEnd = false;

	void HandleCommand(const std::string& commandLine);
	CalcCommand StringToCommand(const std::string& commandString);
	BinarOperator StringToBinarOperator(const std::string& operatorString);
	std::vector<std::string> SplitCommand(std::string commandString);

	void ShowCommands();
	void VarCommand(const std::vector<std::string>& commandArgs);
	void LetCommand(const std::vector<std::string>& commandArgs);
	void FnCommand(const std::vector<std::string>& commandArgs);
	void UnarFnCommand(const std::vector<std::string>& commandArgs);
	void BinarFnCommand(const std::vector<std::string>& commandArgs);
	void PrintCommand(const std::vector<std::string>& commandArgs);
};
