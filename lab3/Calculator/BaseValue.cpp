#include "pch.h"
#include "BaseValue.h"
#include "VarValue.h"
#include "UnarFnValue.h"
#include "BinarFnValue.h"
#include "CallUndefinedValueException.h"
#include "IterativeValueGetter.h"

double BaseValue::Get()
{
	return GetValueFromBaseValuePtr(this->shared_from_this());
}
