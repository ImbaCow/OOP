#include "pch.h"
#include "UnarFnValue.h"
#include "IterativeValueGetter.h"

UnarFnValue::UnarFnValue(const std::shared_ptr<BaseValue>& value)
	: m_valuePtr(value)
{
}

ValueType UnarFnValue::GetType() const
{
	return ValueType::UnarFn;
}

std::shared_ptr<BaseValue> UnarFnValue::GetValuePtr() const
{
	return WeakToSharedPtr(m_valuePtr);
}
