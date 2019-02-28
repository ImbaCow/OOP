#pragma once
#include "pch.h"
#include "CSolidShape.h"

CSolidShape::CSolidShape(uint32_t fillColor, uint32_t outlineColor)
	: m_fillColor(fillColor)
	, CShape(outlineColor)
{
}

uint32_t CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

std::string CSolidShape::ToString() const
{
	return GetShapeInfo() + ' '
		+ std::to_string(GetFillColor()) + ' '
		+ std::to_string(GetOutlineColor());
}
