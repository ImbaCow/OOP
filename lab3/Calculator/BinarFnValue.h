#pragma once
#include "BaseFnValue.h"

enum BinarOperator
{
	PLUS,
	SUB,
	MULT,
	DIV
};

class BinarFnValue : public BaseFnValue
{
public:
	BinarFnValue(std::shared_ptr<BaseValue> firstPtr, std::shared_ptr<BaseValue> secondPtr, BinarOperator op);
	virtual ~BinarFnValue(){};

	ValueType GetType() const override;
	std::shared_ptr<BaseValue> GetFirstPtr() const;
	std::shared_ptr<BaseValue> GetSecondPtr() const;
	BinarOperator GetOp() const;

private:
	std::weak_ptr<BaseValue> m_firstPtr;
	std::weak_ptr<BaseValue> m_secondPtr;
	BinarOperator m_op;
};
