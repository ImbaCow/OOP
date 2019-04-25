#pragma once
#include "BaseValue.h"

double GetValueFromBaseValuePtr(const std::shared_ptr<BaseValue>& valuePtr);
std::shared_ptr<BaseValue> WeakToSharedPtr(const std::weak_ptr<BaseValue>& valuePtr);