#include "IShape.h"
#include "IShapeArray.h"
#include "ShapeFactory.h"
#include "pch.h"

using namespace std;

void GetMaxAreaMinPerimeterShapesFromFile(const string& filePath)
{
	ifstream input(filePath);
	if (!input.is_open())
	{
		cerr << "Input file not found." << endl;
		return;
	}

	IShape* maxAreaShape = nullptr;
	IShape* minPerimeterShape = nullptr;

	try
	{
		IShapeArray shapeArr(input);
		pair<IShape*, IShape*> maxAreaMinPerimeter = shapeArr.GetMaxAreaMinPerimeter();
		IShape* maxAreaShape = maxAreaMinPerimeter.first;
		IShape* minPerimeterShape = maxAreaMinPerimeter.second;
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
		return;
	}

	if (maxAreaShape)
	{
		cout << "Max area shape: " << maxAreaShape->ToString() << "; area: " << maxAreaShape->GetArea() << "; perimeter: " << maxAreaShape->GetPerimeter() << endl;
	}
	if (minPerimeterShape)
	{
		cout << "Min perimeter shape: " << minPerimeterShape->ToString() << "; area: " << minPerimeterShape->GetArea() << "; perimeter: " << minPerimeterShape->GetPerimeter() << endl;
	}
}

int main()
{
	GetMaxAreaMinPerimeterShapesFromFile("input.txt");
}
