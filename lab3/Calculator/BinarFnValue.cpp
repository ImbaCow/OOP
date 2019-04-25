#include "pch.h"
#include "BinarFnValue.h"
#include "IterativeValueGetter.h"

BinarFnValue::BinarFnValue(std::shared_ptr<BaseValue> firstPtr, std::shared_ptr<BaseValue> secondPtr, BinarOperator op)
	: m_firstPtr(firstPtr)
	, m_secondPtr(secondPtr)
	, m_op(op)
{
}

ValueType BinarFnValue::GetType() const
{
	return ValueType::BinarFn;
}

std::shared_ptr<BaseValue> BinarFnValue::GetFirstPtr() const
{
	return WeakToSharedPtr(m_firstPtr);
}

std::shared_ptr<BaseValue> BinarFnValue::GetSecondPtr() const
{
	return WeakToSharedPtr(m_secondPtr);
}

BinarOperator BinarFnValue::GetOp() const
{
	return m_op;
}
