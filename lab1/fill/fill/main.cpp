#include "pch.h"
#include "Field.h"

int main()
{
	std::stringstream ss("O   O #\n  #  #\n # ##\n#");
	Field field(ss);
	field.Fill();
	std::cout << field.ToString();
}
