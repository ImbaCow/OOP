#include "pch.h"
#include "Field.h"

Field::Field(std::istream& input)
{
	std::string lineStr;
	for (size_t line = 0; std::getline(input, lineStr) && line < MAX_Y_SIZE; ++line)
	{
		m_rows.push_back({});
		for (size_t column = 0; column < lineStr.size() && column < MAX_X_SIZE; ++column)
		{
			char currChar = lineStr[column];
			if (currChar == FILL_MARK_CHAR)
			{
				m_marksCoords.push_back({ column, line });
			}
			else if (currChar != BORDER_CHAR)
			{
				currChar = EMPTY_CHAR;
			}
			m_rows[line].push_back(currChar);
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

	return (isCoordsValid && (m_rows[coords.y][coords.x] == EMPTY_CHAR))
		|| (!isCoordsValid && (coords.y < MAX_Y_SIZE) && (coords.x < MAX_X_SIZE));
}

bool Field::IsCoordsValid(const Coords& coords) const
{
	return (coords.y < m_rows.size()) && (coords.x < m_rows[coords.y].size());
}

void Field::ProcessStack(std::stack<Coords>& coordsStack)
{
	Coords current = coordsStack.top();
	coordsStack.pop();
	PaintField({ current.x, current.y }, FILLED_CHAR);

	TryPushCoords({ current.x - 1, current.y }, coordsStack);
	TryPushCoords({ current.x + 1, current.y }, coordsStack);
	TryPushCoords({ current.x, current.y - 1 }, coordsStack);
	TryPushCoords({ current.x, current.y + 1 }, coordsStack);
}

void Field::TryPushCoords(const Coords& coords, std::stack<Coords>& coordsStack)
{
	if (CanFill({ coords.x, coords.y }))
	{
		coordsStack.push({ coords.x, coords.y });
	}
}

void Field::PaintField(const Coords& paintCoords, char paintChar)
{
	if (m_rows.size() <= paintCoords.y)
	{
		m_rows.resize(paintCoords.y + 1);
	}

	if (m_rows[paintCoords.y].size() <= paintCoords.x)
	{
		m_rows[paintCoords.y].resize(paintCoords.x + 1, EMPTY_CHAR);
	}

	m_rows[paintCoords.y][paintCoords.x] = paintChar;
}

std::string Field::ToString() const
{
	std::string resultString;
	for (const auto& line : m_rows)
	{
		for (char field : line)
		{
			resultString += field;
		}
		resultString += '\n';
	}
	return resultString;
}
