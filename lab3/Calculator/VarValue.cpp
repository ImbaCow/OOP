#include "pch.h"
#include "VarValue.h"

VarValue::VarValue(double value)
	: m_value(value)
{
}

VarValue::VarValue()
	: m_value(std::nullopt)
{
}

void VarValue::Set(double newValue)
{
	m_value = newValue;
}

ValueType VarValue::GetType() const
{
	return ValueType::Var;
}

std::optional<double> VarValue::GetValue() const
{
	return m_value;
}
