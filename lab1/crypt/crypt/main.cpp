#include "pch.h"
#include "SwapEncryptor.h"
#include "boost/lexical_cast.hpp"

using namespace std;

optional<uint8_t> GetKeyFromString(const std::string& keyString)
{
	uint32_t keyInt;

	try
	{
		keyInt = boost::lexical_cast<uint32_t>(keyString);
	}
	catch (const boost::exception&)
	{
		return std::nullopt;
	}

	if (keyInt > 255)
	{
		return std::nullopt;
	}
	return static_cast<uint8_t>(keyInt);
}

int main(int argc, char* argv[])
{
	if (argc < 5)
	{
		cerr << "Command must be in format: \"crypt.exe <crypt|decrypt> <input file> <output file> <key>\"" << endl;
		return 1;
	}

	ifstream input(argv[2]);
	if (!input.is_open())
	{
		cerr << "Input file not found" << endl;
		return 1;
	}
	ofstream output(argv[3]);
	if (!output.is_open())
	{
		cerr << "Output file not found" << endl;
		return 1;
	}

	auto keyOpt = GetKeyFromString(argv[4]);
	if (!keyOpt)
	{
		cerr << "Invalid key argument. Must be int in range 0-255, \"" << argv[4] << "\" given." << endl;
		return 1;
	}
	uint8_t key = keyOpt.value();

	try
	{
		SwapEncryptor encryptor(key);
		encryptor.encryptStream(argv[1], input, output);
	}
	catch (const std::invalid_argument& e)
	{
		cerr << e.what() << endl;
		return 1;
	}
}
