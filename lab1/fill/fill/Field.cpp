#include "pch.h"
#include "Field.h"

Field::Field(std::istream& input)
{
	std::string lineStr;
	for (size_t line = 0; std::getline(input, lineStr) && line < MAX_Y_SIZE; ++line)
	{
		m_fields.push_back({});
		for (size_t column = 0; column < lineStr.size() && column < MAX_X_SIZE; ++column)
		{
			char currChar = lineStr[column];
			if (currChar == FILL_MARK_CHAR)
			{
				m_marksCoords.push_back({ column, line });
			}
			else if (currChar != BORDER_CHAR && currChar != '\n')
			{
				currChar = EMPTY_CHAR;
			}
			if (currChar != '\n')
			{
				m_fields[line].push_back(currChar);
			}
		}
	}
}

void Field::Fill()
{
	for (const auto& markCoords : m_marksCoords)
	{
		IteratFill({ markCoords.x - 1, markCoords.y });
		IteratFill({ markCoords.x + 1, markCoords.y });
		IteratFill({ markCoords.x, markCoords.y - 1 });
		IteratFill({ markCoords.x, markCoords.y + 1 });
	}
}

void Field::IteratFill(const Coords& coords)
{
	if (!CanFill(coords))
	{
		return;
	}

	std::stack<Coords> coordsStack;
	coordsStack.push(coords);
	while (!coordsStack.empty())
	{
		ProcessStack(coordsStack);
	}
}

bool Field::CanFill(const Coords& coords) const
{
	bool isCoordsValid = IsCoordsValid(coords);

	return (isCoordsValid && (m_fields[coords.y][coords.x] == EMPTY_CHAR))
		|| (!isCoordsValid && (coords.y < MAX_Y_SIZE) && (coords.x < MAX_X_SIZE));
}

bool Field::IsCoordsValid(const Coords& coords) const
{
	return (coords.y < m_fields.size()) && (coords.x < m_fields[coords.y].size());
}

void Field::ProcessStack(std::stack<Coords>& coordsStack)
{
	Coords current = coordsStack.top();
	coordsStack.pop();
	PaintField({ current.x, current.y }, FILLED_CHAR);

	if (CanFill({ current.x - 1, current.y }))
	{
		coordsStack.push({ current.x - 1, current.y });
	}
	if (CanFill({ current.x + 1, current.y }))
	{
		coordsStack.push({ current.x + 1, current.y });
	}
	if (CanFill({ current.x, current.y - 1 }))
	{
		coordsStack.push({ current.x, current.y - 1 });
	}
	if (CanFill({ current.x, current.y + 1 }))
	{
		coordsStack.push({ current.x, current.y + 1 });
	}
}

void Field::PaintField(const Coords& paintCoords, char paintChar)
{
	while (m_fields.size() <= paintCoords.y)
	{
		m_fields.push_back({});
	}

	while (m_fields[paintCoords.y].size() <= paintCoords.x)
	{
		m_fields[paintCoords.y].push_back(EMPTY_CHAR);
	}

	m_fields[paintCoords.y][paintCoords.x] = paintChar;
}

std::string Field::ToString() const
{
	std::string resultString;
	for (const auto& line : m_fields)
	{
		for (char field : line)
		{
			resultString += field;
		}
		resultString += '\n';
	}
	return resultString;
}
