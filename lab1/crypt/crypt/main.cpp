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

void EncryptFile(const string& cryptMode, const string& inputFileName, const string& outputFileName, const string& keyString)
{
	ifstream input(inputFileName, ios::binary);
	if (!input.is_open())
	{
		throw invalid_argument("Input file not found");
	}
	ofstream output(outputFileName, ios::binary);
	if (!output.is_open())
	{
		throw invalid_argument("Output file not found");
	}

	auto keyOpt = GetKeyFromString(keyString);
	if (!keyOpt)
	{
		throw invalid_argument("Invalid key argument. Must int in range 0-255, \"" + keyString + "\" given.");
	}
	uint8_t key = keyOpt.value();

	EncryptStream(cryptMode, input, output, key);
}

int main(int argc, char* argv[])
{
	if (argc < 5)
	{
		cerr << "Command must be in format: \"crypt.exe <crypt|decrypt> <input file> <output file> <key>\"" << endl;
		return 1;
	}

	try
	{
		EncryptFile(argv[1], argv[2], argv[3], argv[4]);
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
		return 1;
	}
}
