#pragma once
#include "BaseValue.h"

class VarValue : public BaseValue
{
public:
	VarValue();
	VarValue(double value);
	virtual ~VarValue(){};

	void Set(double value) override;
	ValueType GetType() const override;
	std::optional<double> GetValue() const;

private:
	std::optional<double> m_value;
};
