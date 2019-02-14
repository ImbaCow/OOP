#pragma once
#include "ISolidShape.h"
#include "pch.h"

uint32_t ISolidShape::GetFillColor() const
{
	return m_fillColor;
}

void ISolidShape::SetFillColorByString(const std::string& string)
{
	try
	{
		m_fillColor = HexStringToUint(string);
	}
	catch (const std::invalid_argument&)
	{
		throw std::invalid_argument("Fill color must be hex");
	}
}
