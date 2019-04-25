#pragma once
#include "pch.h"

enum ValueType
{
	Var,
	UnarFn,
	BinarFn
};

class BaseValue : public std::enable_shared_from_this<BaseValue>
{
public:
	virtual ~BaseValue(){};

	virtual ValueType GetType() const = 0;
	virtual void Set(double value) = 0;
	double Get();
};
