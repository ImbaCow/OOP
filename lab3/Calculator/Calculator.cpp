#include "pch.h"
#include "Calculator.h"
#include "IterativeValueGetter.h"
#include "CallUndefinedValueException.h"

void Calculator::Var(const std::string& newVariableName)
{
	InsertVariable(newVariableName, std::make_shared<VarValue>());
}

void Calculator::Let(const std::string& toVariableName, double newValue)
{
	auto it = m_valueMap.find(toVariableName);
	if (it == m_valueMap.end())
	{
		m_valueMap.insert({ toVariableName, std::make_shared<VarValue>(newValue) });
	}
	else
	{
		it->second->Set(newValue);
	}
}

void Calculator::Let(const std::string& toVariableName, const std::string& fromVariableName)
{
	double value = GetValueFromBaseValuePtr(GetVariable(fromVariableName));

	Let(toVariableName, value);
}

void Calculator::Fn(const std::string& toFnName, const std::string& fromVariableName)
{
	std::shared_ptr<BaseValue> value = GetVariable(fromVariableName);

	InsertVariable(toFnName, std::make_shared<UnarFnValue>(value));
}

void Calculator::Fn(const std::string& toFnName, const std::string& firstVariableName, const std::string& secondVariableName, BinarOperator op)
{
	std::shared_ptr<BaseValue> firstValue = GetVariable(firstVariableName);
	std::shared_ptr<BaseValue> secondValue = GetVariable(secondVariableName);

	InsertVariable(toFnName, std::make_shared<BinarFnValue>(firstValue, secondValue, op));
}

void Calculator::Print(const std::string& valueName, std::ostream& out)
{
	out << ValueToString(GetVariable(valueName)) << std::endl;
} 

void Calculator::PrintVars(std::ostream& out)
{
	for (const auto& mapItem : m_valueMap)
	{
		if (mapItem.second->GetType() == ValueType::Var)
		{
			out << mapItem.first << ':' << ValueToString(mapItem.second) << std::endl;
		}
	}
}

void Calculator::PrintFns(std::ostream& out)
{
	for (const auto& mapItem : m_valueMap)
	{
		switch (mapItem.second->GetType())
		{
		case ValueType::UnarFn:
		case ValueType::BinarFn:
			out << mapItem.first << ':' << ValueToString(mapItem.second) << std::endl;
			break;
		default:
			break;
		}
	}
}

std::shared_ptr<BaseValue> Calculator::GetVariable(const std::string& variableName)
{
	auto it = m_valueMap.find(variableName);
	if (it == m_valueMap.end())
	{
		throw std::logic_error("Variable '" + variableName + "' does not exist.");
	}

	return it->second;
}

void Calculator::InsertVariable(const std::string& variableName, const std::shared_ptr<BaseValue>& value)
{
	auto it = m_valueMap.find(variableName);
	if (it != m_valueMap.end())
	{
		throw std::logic_error("Variable '" + variableName + "' already exist.");
	}

	m_valueMap.insert({ variableName, value });
}

std::string Calculator::ValueToString(const std::shared_ptr<BaseValue>& valuePtr)
{
	std::string result;
	try
	{
		double value = GetValueFromBaseValuePtr(valuePtr);
		result = doubleToString(value);
	}
	catch (const CallUndefinedValueException&)
	{
		result = "nan";
	}

	return result;
}

std::string Calculator::doubleToString(double num)
{
	std::stringstream ss;
	ss.precision(2);
	ss << std::fixed << num;

	return ss.str();
}
