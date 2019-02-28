#pragma once
#include "pch.h"
#include "CShape.h"

CShape::CShape(uint32_t outlineColor)
	: m_outlineColor(outlineColor)
{
}

uint32_t CShape::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CShape::ToString() const
{
	return GetShapeInfo() + ' '
		+ std::to_string(GetOutlineColor());
}
