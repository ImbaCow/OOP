#include "pch.h"
#include "CallUndefinedValueException.h"
#include "IterativeValueGetter.h"
#include "VarValue.h"
#include "UnarFnValue.h"
#include "BinarFnValue.h"

double CalulateBinarFnValue(double firstArg, double secondArg, BinarOperator op)
{
	double result;
	switch (op)
	{
	case PLUS:
		result = firstArg + secondArg;
		break;
	case SUB:
		result = firstArg - secondArg;
		break;
	case MULT:
		result = firstArg * secondArg;
		break;
	case DIV:
		if (std::abs(secondArg) < std::numeric_limits<double>::epsilon())
		{
			throw std::invalid_argument("Division by zero");
		}
		result = firstArg / secondArg;
		break;
	default:
		throw std::invalid_argument("Unhandled operation");
	}

	return result;
}

void visitVarPtr(const std::shared_ptr<BaseValue>& varPtr, std::map<std::shared_ptr<BaseValue>, double>& calculatedValues)
{
	std::shared_ptr<VarValue> variablePtr = std::dynamic_pointer_cast<VarValue>(varPtr);
	if (!variablePtr->GetValue())
	{
		throw CallUndefinedValueException("Undefined variable");
	}
	calculatedValues[varPtr] = variablePtr->GetValue().value();
}

void visitUnarFnPtr(const std::shared_ptr<BaseValue>& unarFnPtr, std::map<std::shared_ptr<BaseValue>, double>& calculatedValues)
{
	std::shared_ptr<UnarFnValue> variablePtr = std::dynamic_pointer_cast<UnarFnValue>(unarFnPtr);
	calculatedValues[unarFnPtr] = calculatedValues[variablePtr->GetValuePtr()];
}

void visitBinarFnPtr(const std::shared_ptr<BaseValue>& binarFnPtr, std::map<std::shared_ptr<BaseValue>, double>& calculatedValues)
{
	std::shared_ptr<BinarFnValue> variablePtr = std::dynamic_pointer_cast<BinarFnValue>(binarFnPtr);

	double firstArg = calculatedValues[variablePtr->GetFirstPtr()];
	double secondArg = calculatedValues[variablePtr->GetSecondPtr()];
	BinarOperator op = variablePtr->GetOp();

	calculatedValues[binarFnPtr] = CalulateBinarFnValue(firstArg, secondArg, op);
}

bool IsCalculated(const std::shared_ptr<BaseValue>& valuePtr, std::map<std::shared_ptr<BaseValue>, double>& calculatedValues)
{
	auto calculatedValue = calculatedValues.find(valuePtr);

	return calculatedValue != calculatedValues.end();
}

double GetValueFromBaseValuePtr(const std::shared_ptr<BaseValue>& valuePtr)
{
	std::stack<std::shared_ptr<BaseValue>> ptrStack;
	std::map<std::shared_ptr<BaseValue>, double> calculatedValues;

	std::shared_ptr<BaseValue> currentPtr = valuePtr;

	if (valuePtr->GetType() == ValueType::Var)
	{
		visitVarPtr(valuePtr, calculatedValues);
	}
	while (!ptrStack.empty() || !IsCalculated(currentPtr, calculatedValues))
	{
		if (currentPtr->GetType() == ValueType::Var && !IsCalculated(currentPtr, calculatedValues))
		{
			visitVarPtr(currentPtr, calculatedValues);
		}
		if (!IsCalculated(currentPtr, calculatedValues))
		{
			ptrStack.push(currentPtr);
			switch (currentPtr->GetType())
			{
			case ValueType::UnarFn:
			{
				std::shared_ptr<BaseValue> fnArgPtr = std::dynamic_pointer_cast<UnarFnValue>(currentPtr)->GetValuePtr();
				currentPtr = fnArgPtr;
				break;
			}
			case ValueType::BinarFn:
			{
				std::shared_ptr<BaseValue> fnArgPtr = std::dynamic_pointer_cast<BinarFnValue>(currentPtr)->GetFirstPtr();
				currentPtr = fnArgPtr;
				break;
			}
			default:
				break;
			}
		}
		else
		{
			std::shared_ptr<BaseValue> stackTopPtr = ptrStack.top();
			if (stackTopPtr->GetType() == ValueType::BinarFn)
			{
				std::shared_ptr<BaseValue> rightPtr = std::dynamic_pointer_cast<BinarFnValue>(stackTopPtr)->GetSecondPtr();
				if (!IsCalculated(rightPtr, calculatedValues))
				{
					currentPtr = rightPtr;
					continue;
				}
				else
				{
					visitBinarFnPtr(stackTopPtr, calculatedValues);
				}
			}
			else
			{
				visitUnarFnPtr(stackTopPtr, calculatedValues);
			}
			ptrStack.pop();
		}
	}

	return calculatedValues[valuePtr];
}

std::shared_ptr<BaseValue> WeakToSharedPtr(const std::weak_ptr<BaseValue>& valuePtr)
{
	return valuePtr.lock();
}
