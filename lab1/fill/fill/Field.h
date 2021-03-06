#pragma once

const size_t MAX_X_SIZE = 100;
const size_t MAX_Y_SIZE = 100;

const char FILL_MARK_CHAR = 'O';
const char BORDER_CHAR = '#';
const char FILLED_CHAR = '-';
const char EMPTY_CHAR = ' ';

struct Coords
{
	size_t x;
	size_t y;
};

class Field
{
public:
	Field(std::istream& input);

	void Fill();
	std::string ToString() const;

private:
	std::vector<std::vector<char>> m_rows;
	std::vector<Coords> m_marksCoords;

	void IteratFill(const Coords& coords);
	void PaintField(const Coords& paintCoords, char paintChar);
	void ProcessStack(std::stack<Coords>& coordsStack);
	void TryPushCoords(const Coords& coords, std::stack<Coords>& coordsStack);

	bool IsCoordsValid(const Coords& coords) const;
	bool CanFill(const Coords& coords) const;
};
