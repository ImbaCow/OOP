#pragma once
#include "BinarFnValue.h"
#include "UnarFnValue.h"
#include "VarValue.h"

class Calculator
{
public:
	void Var(const std::string& newVariableName);

	void Let(const std::string& toVariableName, double newValue);
	void Let(const std::string& toVariableName, const std::string& fromVariableName);

	void Fn(const std::string& toFnName, const std::string& fromVariableName);
	void Fn(const std::string& toFnName, const std::string& firstVariableName, const std::string& secondVariableName, BinarOperator op);

	void Print(const std::string& valueName, std::ostream& out);
	void PrintVars(std::ostream& out);
	void PrintFns(std::ostream& out);

private:
	std::map<std::string, std::shared_ptr<BaseValue>> m_valueMap;

	std::shared_ptr<BaseValue> GetVariable(const std::string& variableName);
	void InsertVariable(const std::string& variableName, const std::shared_ptr<BaseValue>& value);

	std::string ValueToString(const std::shared_ptr<BaseValue>& valuePtr);
	std::string doubleToString(double num);
};
