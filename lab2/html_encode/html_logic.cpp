#pragma once 
#include "pch.h"
#include "html_logic.h"

std::string HtmlCharEncode(char ch)
{
	switch (ch)
	{
	case '<':
		return "&lt;";
	case '>':
		return "&gt;";
	case '"':
		return "&quot;";
	case '\'':
		return "&apos;";
	case '&':
		return "&amp;";
	default:
		return std::string(1, ch);
	}
}

std::string HtmlEncode(const std::string & text)
{
	std::string result;
	for (char ch : text)
	{
		result += HtmlCharEncode(ch);
	}
	return result;
}
