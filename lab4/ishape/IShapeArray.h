#pragma once
#include "IShape.h"
#include "ShapeFactory.h"

class IShapeArray
{
public:
	IShapeArray(std::istream& inputStream);
	~IShapeArray();

	std::pair<IShape*, IShape*> GetMaxAreaMinPerimeter() const;
	void SetShapeArrayFromStream(std::istream& inputStream);
	std::string ToString() const;

private:
	std::vector<IShape*> shapeArr;
	void Clear();
};
