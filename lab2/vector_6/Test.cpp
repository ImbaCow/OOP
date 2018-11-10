#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "MyArray.h"
#include <string>

using namespace std; 

BOOST_AUTO_TEST_CASE(myTestCase)
{
	MyArray array;
	string input = "12.2 12 12.1231212";

	array.AddItemsFormString(input);
	array.ProcessArray();
	array.SortArray();
}