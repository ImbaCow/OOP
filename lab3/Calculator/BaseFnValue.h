#pragma once
#include "BaseValue.h"

class BaseFnValue : public BaseValue
{
public:
	virtual ~BaseFnValue(){};

	void Set(double value) override;
};
