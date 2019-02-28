#pragma once
#include "pch.h"
#include "CLineSegment.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"

std::unique_ptr<IShape> CreateShape(const std::string& shapeInfo);
