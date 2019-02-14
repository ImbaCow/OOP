#include "IShapeArray.h"
#include "pch.h"

IShapeArray::IShapeArray(std::istream& inputStream)
{
	SetShapeArrayFromStream(inputStream);
}

IShapeArray::~IShapeArray()
{
	Clear();
}

std::pair<IShape*, IShape*> IShapeArray::GetMaxAreaMinPerimeter() const
{
	IShape* maxAreaShape = nullptr;
	IShape* minPerimeterShape = nullptr;

	for (auto shape : shapeArr)
	{
		if (!maxAreaShape || maxAreaShape->GetArea() < shape->GetArea())
		{
			maxAreaShape = shape;
		}
		if (!minPerimeterShape || minPerimeterShape->GetPerimeter() > shape->GetPerimeter())
		{
			minPerimeterShape = shape;
		}
	}
	return { maxAreaShape, minPerimeterShape };
}

void IShapeArray::SetShapeArrayFromStream(std::istream& inputStream)
{
	std::string command;

	for (size_t lineNumber = 1; std::getline(inputStream, command); ++lineNumber)
	{
		try
		{
			shapeArr.push_back(ShapeFactory::GetShape(command));
		}
		catch (const std::exception& e)
		{
			Clear();
			throw std::invalid_argument("Error on line " + std::to_string(lineNumber) + ". " + e.what());
		}
	}
}

std::string IShapeArray::ToString() const
{
	std::string result;
	for (auto shape : shapeArr)
	{
		result += shape->ToString() + '\n';
	}
	return result;
}

void IShapeArray::Clear()
{
	for (auto shape : shapeArr)
	{
		delete shape;
	}
	shapeArr.clear();
}
