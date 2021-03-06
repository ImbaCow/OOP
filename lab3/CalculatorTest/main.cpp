#pragma once
#include "pch.h"
#include "../Calculator/IterativeValueGetter.h"
#include "../Calculator/BaseFnValue.h"
#include "../Calculator/BaseValue.h"
#include "../Calculator/BinarFnValue.h"
#include "../Calculator/Calculator.h"
#include "../Calculator/CallUndefinedValueException.h"
#include "../Calculator/ConsoleCalculator.h"
#include "../Calculator/UnarFnValue.h"
#include "../Calculator/VarValue.h"

#define DOUBLE_COMPARE_EPSILION 0.01
#define STACK_OVERFLOW_TEST_DEPTH 1000000

#define BOOST_TEST_MODULE CalculatorTest
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(testVariables)

	BOOST_AUTO_TEST_SUITE(testVar)
		BOOST_AUTO_TEST_CASE(testGetNaNValue)
		{
			shared_ptr<BaseValue> varPtr = make_shared<VarValue>();

			BOOST_CHECK_THROW(varPtr->Get(), CallUndefinedValueException);
		}
		BOOST_AUTO_TEST_CASE(testGetValue)
		{
			shared_ptr<BaseValue> varPtr = make_shared<VarValue>(3);

			BOOST_CHECK_CLOSE_FRACTION(varPtr->Get(), 3, DOUBLE_COMPARE_EPSILION);
		}
		BOOST_AUTO_TEST_CASE(testSetValue)
		{
			shared_ptr<BaseValue> varPtr = make_shared<VarValue>();
			varPtr->Set(3);

			BOOST_CHECK_CLOSE_FRACTION(varPtr->Get(), 3, DOUBLE_COMPARE_EPSILION);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct DefinedVarPtrFixture
	{
		DefinedVarPtrFixture()
			: variable(make_shared<VarValue>())
		{
		}

		shared_ptr<BaseValue> variable;
	};
	BOOST_FIXTURE_TEST_SUITE(testUnarFn, DefinedVarPtrFixture)
		BOOST_AUTO_TEST_CASE(testGetNaNValue)
		{
			shared_ptr<BaseValue> unarFnPtr = make_shared<UnarFnValue>(variable);

			BOOST_CHECK_THROW(unarFnPtr->Get(), CallUndefinedValueException);
		}
		BOOST_AUTO_TEST_CASE(testGetVarValue)
		{
			variable->Set(3);
			shared_ptr<BaseValue> unarFnPtr = make_shared<UnarFnValue>(variable);

			BOOST_CHECK_CLOSE_FRACTION(unarFnPtr->Get(), 3, DOUBLE_COMPARE_EPSILION);
		}
		BOOST_AUTO_TEST_CASE(testChangeVarValue)
		{
			variable->Set(3);
			shared_ptr<BaseValue> unarFnPtr = make_shared<UnarFnValue>(variable);
			variable->Set(5);

			BOOST_CHECK_CLOSE_FRACTION(unarFnPtr->Get(), 5, DOUBLE_COMPARE_EPSILION);
		}
		BOOST_AUTO_TEST_CASE(testGetFnValue)
		{
			variable->Set(3);
			shared_ptr<BaseValue> firstUnarFnPtr = make_shared<UnarFnValue>(variable);
			shared_ptr<BaseValue> secondUnarFnPtr = make_shared<UnarFnValue>(firstUnarFnPtr);

			BOOST_CHECK_CLOSE_FRACTION(secondUnarFnPtr->Get(), 3, DOUBLE_COMPARE_EPSILION);
		}
		BOOST_AUTO_TEST_CASE(testSetValue)
		{
			shared_ptr<BaseValue> unarFnPtr = make_shared<UnarFnValue>(variable);

			BOOST_CHECK_THROW(unarFnPtr->Set(3), exception);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct DefinedVarsPtrFixture
	{
		DefinedVarsPtrFixture()
			: firstVariable(make_shared<VarValue>())
			, secondVariable(make_shared<VarValue>())
		{
		}

		shared_ptr<BaseValue> firstVariable;
		shared_ptr<BaseValue> secondVariable;
	};
	BOOST_FIXTURE_TEST_SUITE(testBinarFn, DefinedVarsPtrFixture)
		BOOST_AUTO_TEST_CASE(testOperators)
		{
			firstVariable->Set(3);
			secondVariable->Set(5);

			shared_ptr<BaseValue> plusFnPtr = make_shared<BinarFnValue>(firstVariable, secondVariable, BinarOperator::PLUS);
			BOOST_CHECK_CLOSE_FRACTION(plusFnPtr->Get(), 8, DOUBLE_COMPARE_EPSILION);

			shared_ptr<BaseValue> subFnPtr = make_shared<BinarFnValue>(firstVariable, secondVariable, BinarOperator::SUB);
			BOOST_CHECK_CLOSE_FRACTION(subFnPtr->Get(), -2, DOUBLE_COMPARE_EPSILION);

			shared_ptr<BaseValue> multFnPtr = make_shared<BinarFnValue>(firstVariable, secondVariable, BinarOperator::MULT);
			BOOST_CHECK_CLOSE_FRACTION(multFnPtr->Get(), 15, DOUBLE_COMPARE_EPSILION);

			shared_ptr<BaseValue> divFnPtr = make_shared<BinarFnValue>(firstVariable, secondVariable, BinarOperator::DIV);
			BOOST_CHECK_CLOSE_FRACTION(divFnPtr->Get(), 0.6, DOUBLE_COMPARE_EPSILION);
		}
		BOOST_AUTO_TEST_CASE(testDivOnZero)
		{
			firstVariable->Set(3);
			secondVariable->Set(0);

			shared_ptr<BaseValue> divFnPtr = make_shared<BinarFnValue>(firstVariable, secondVariable, BinarOperator::DIV);
			BOOST_CHECK_THROW(divFnPtr->Get(), invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(testGetNaNValue)
		{
			firstVariable->Set(3);

			shared_ptr<BaseValue> plusFnPtr = make_shared<BinarFnValue>(firstVariable, secondVariable, BinarOperator::PLUS);
			BOOST_CHECK_THROW(plusFnPtr->Get(), CallUndefinedValueException);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

struct CalculatorFixture
{
	Calculator calc;
};
BOOST_FIXTURE_TEST_SUITE(testCalculator, CalculatorFixture)
	BOOST_AUTO_TEST_CASE(testPrint)
	{
		calc.Let("var1", 3);

		stringstream ss;
		calc.Print("var1", ss);
		BOOST_CHECK_EQUAL(ss.str(), "3.00\n");
	}
	BOOST_AUTO_TEST_CASE(testPrintNaN)
	{
		calc.Var("var1");

		stringstream ss;
		calc.Print("var1", ss);
		BOOST_CHECK_EQUAL(ss.str(), "nan\n");
	}
	BOOST_AUTO_TEST_CASE(testLet)
	{
		calc.Let("var1", 3);
		calc.Fn("fn1", "var1");
		calc.Let("var2", "fn1");

		stringstream ss1;
		stringstream ss2;

		calc.Print("var1", ss1);
		calc.Print("fn1", ss2);

		BOOST_CHECK_EQUAL(ss1.str(), ss2.str());
	}
	BOOST_AUTO_TEST_CASE(testFn)
	{
		calc.Let("var1", 3);
		calc.Let("var2", 5);
		calc.Fn("fn1", "var1");
		calc.Fn("fn2", "var1", "var2", BinarOperator::PLUS);

		stringstream ss1;
		stringstream ss2;

		calc.Print("fn1", ss1);
		calc.Print("fn2", ss2);

		BOOST_CHECK_EQUAL(ss1.str(), "3.00\n");
		BOOST_CHECK_EQUAL(ss2.str(), "8.00\n");
		BOOST_CHECK_THROW(calc.Fn("fn1", "fn2"), exception);
	}
	BOOST_AUTO_TEST_CASE(testPrintMulti)
	{
		calc.Let("var1", 3);
		calc.Let("var2", 5);
		calc.Fn("fn1", "var1");
		calc.Fn("fn2", "var2");

		stringstream ss1;
		stringstream ss2;

		calc.PrintVars(ss1);
		calc.PrintFns(ss2);

		BOOST_CHECK_EQUAL(ss1.str(), "var1:3.00\nvar2:5.00\n");
		BOOST_CHECK_EQUAL(ss2.str(), "fn1:3.00\nfn2:5.00\n");
	}
BOOST_AUTO_TEST_SUITE_END()

struct ConsoleCalculatorFixture
{
	ConsoleCalculatorFixture()
		: consoleCalc(iss, oss)
	{
	}

	void fillStreamWithHelpCommandText(stringstream& ss)
	{
		ss << "help - Show commands list" << std::endl
		   << "stop - Stop console calculator process" << std::endl
		   << "var <name1> - Define new variable" << std::endl
		   << "let <name1> = <double> - Initialize variable with double" << std::endl
		   << "let <name1> = <name2> - Initialize variable with another variable value" << std::endl
		   << "fn <name1> = <name2> - Initialize function with another value link" << std::endl
		   << "fn <name1> = <name2> <operation> <name3> - Initialize function with expression(+,-,*,/)" << std::endl
		   << "print <name1> - Show variable or function value" << std::endl
		   << "printvars - Show all variables value" << std::endl
		   << "printfns - Show all functions value" << std::endl;
	}

	ConsoleCalculator consoleCalc;
	stringstream iss;
	stringstream oss;
};
BOOST_FIXTURE_TEST_SUITE(testConsoleCalculator, ConsoleCalculatorFixture)
	BOOST_AUTO_TEST_CASE(testBegin)
	{
		iss << "stop";
		consoleCalc.Start();

		stringstream expectedSs("");
		fillStreamWithHelpCommandText(expectedSs);
		expectedSs << "Calculator end" << std::endl;
		BOOST_CHECK_EQUAL(oss.str(), expectedSs.str());
	}
	BOOST_AUTO_TEST_CASE(testVarCommand)
	{
		iss << "var var1" << std::endl
			<< "var var1" << std::endl
			<< "print var1" << std::endl
			<< "stop";
		consoleCalc.Start();

		stringstream expectedSs("");
		fillStreamWithHelpCommandText(expectedSs);

		expectedSs << "Variable 'var1' already exist." << std::endl
				   << "Enter 'help' to show commands list." << std::endl
				   << "nan" << std::endl;

		expectedSs << "Calculator end" << std::endl;
		BOOST_CHECK_EQUAL(oss.str(), expectedSs.str());
	}
	BOOST_AUTO_TEST_CASE(testLetCommand)
	{
		iss << "let var1 = 3" << std::endl
			<< "let var2 = 4" << std::endl
			<< "print var1" << std::endl
			<< "let var1 = var2" << std::endl
			<< "print var1" << std::endl
			<< "stop";
		consoleCalc.Start();

		stringstream expectedSs("");
		fillStreamWithHelpCommandText(expectedSs);

		expectedSs << "3.00" << std::endl
				   << "4.00" << std::endl;

		expectedSs << "Calculator end" << std::endl;
		BOOST_CHECK_EQUAL(oss.str(), expectedSs.str());
	}
	BOOST_AUTO_TEST_CASE(testFnCommand)
	{
		iss << "let var1 = 3" << std::endl
			<< "let var2 = 5" << std::endl
			<< "fn fn1 = var1" << std::endl
			<< "fn fn2 = var1 + var2" << std::endl
			<< "fn fn3 = fn1 * fn2" << std::endl
			<< "fn fn4 = var2 - var1" << std::endl
			<< "fn fn5 = fn3 / fn4" << std::endl
			<< "print fn5" << std::endl
			<< "stop";
		consoleCalc.Start();

		stringstream expectedSs("");
		fillStreamWithHelpCommandText(expectedSs);

		expectedSs << "12.00" << std::endl;

		expectedSs << "Calculator end" << std::endl;
		BOOST_CHECK_EQUAL(oss.str(), expectedSs.str());
	}
	BOOST_AUTO_TEST_CASE(testLetFnCommand)
	{
		iss << "let var1 = 3" << std::endl
			<< "fn fn1 = var1" << std::endl
			<< "fn fn2 = var1" << std::endl
			<< "let fn1 = fn2" << std::endl
			<< "stop";
		consoleCalc.Start();

		stringstream expectedSs("");
		fillStreamWithHelpCommandText(expectedSs);

		expectedSs << "Cannot set 3.000000 to function" << std::endl
				   << "Enter 'help' to show commands list." << std::endl;

		expectedSs << "Calculator end" << std::endl;
		BOOST_CHECK_EQUAL(oss.str(), expectedSs.str());
	}
	BOOST_AUTO_TEST_CASE(testPrintVars)
	{
		iss << "let var2 = 3" << std::endl
			<< "let var1 = 4" << std::endl
			<< "fn fn1 = var1" << std::endl
			<< "fn fn2 = var2" << std::endl
			<< "printvars" << std::endl
			<< "stop";
		consoleCalc.Start();

		stringstream expectedSs("");
		fillStreamWithHelpCommandText(expectedSs);

		expectedSs << "var1:4.00" << std::endl
				   << "var2:3.00" << std::endl;

		expectedSs << "Calculator end" << std::endl;
		BOOST_CHECK_EQUAL(oss.str(), expectedSs.str());
	}
	BOOST_AUTO_TEST_CASE(testPrintFns)
	{
		iss << "let var2 = 3" << std::endl
			<< "let var1 = 4" << std::endl
			<< "fn fn2 = var1" << std::endl
			<< "fn fn1 = var2" << std::endl
			<< "printfns" << std::endl
			<< "stop";
		consoleCalc.Start();

		stringstream expectedSs("");
		fillStreamWithHelpCommandText(expectedSs);

		expectedSs << "fn1:3.00" << std::endl
				   << "fn2:4.00" << std::endl;

		expectedSs << "Calculator end" << std::endl;
		BOOST_CHECK_EQUAL(oss.str(), expectedSs.str());
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(testStackOverflow)
{
	Calculator calc;
	calc.Let("variable", 1);
	calc.Fn("fn0", "variable");
	string currentFnName = "";

	for (size_t i = 1; i < STACK_OVERFLOW_TEST_DEPTH; ++i)
	{
		string previousFnName = "fn" + to_string(i - 1);
		currentFnName = "fn" + to_string(i);
		calc.Fn(currentFnName, previousFnName, "variable", BinarOperator::PLUS);
	}

	stringstream result("");
	calc.Print(currentFnName, result);
	BOOST_CHECK_EQUAL(result.str(), to_string(STACK_OVERFLOW_TEST_DEPTH) + ".00\n");
}