#pragma once
#include "BaseFnValue.h"

class UnarFnValue : public BaseFnValue
{
public:
	UnarFnValue(const std::shared_ptr<BaseValue>& value);
	virtual ~UnarFnValue(){};

	ValueType GetType() const override;
	std::shared_ptr<BaseValue> GetValuePtr() const;

private:
	std::weak_ptr<BaseValue> m_valuePtr;
};
