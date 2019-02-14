#pragma once
#include "IShape.h"
#include "pch.h"

uint32_t IShape::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t IShape::HexStringToUint(const std::string& string)
{
	std::stringstream ss;
	ss << std::hex << string;
	uint32_t result;
	if (!(ss >> result))
	{
		throw std::invalid_argument("String must be hex");
	}
	return result;
}

void IShape::SetOutlineColorByString(const std::string& string)
{
	try
	{
		m_outlineColor = HexStringToUint(string);
	}
	catch (const std::invalid_argument&)
	{
		throw std::invalid_argument("Outline color must be hex");
	}
}
