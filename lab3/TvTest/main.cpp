#pragma once
#include "pch.h"
#include "CTVSet.h"
#define BOOST_TEST_MODULE TvTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestFuzzyCompare)

BOOST_AUTO_TEST_CASE(testTvCreation) {
	CTVSet tv;

	int currChannel = tv.GetCurrChannel();
	BOOST_CHECK(currChannel == 0);

	tv.TurnOn();
	currChannel = tv.GetCurrChannel();
	BOOST_CHECK(currChannel == 1);

	std::string currChannelName = tv.GetChannelName(1);
	BOOST_CHECK(currChannelName.empty());
}

BOOST_AUTO_TEST_CASE(testNumberChannelSelect) {
	CTVSet tv;
	try
	{
		tv.SelectChannel(56);
	}
	catch (const std::exception&)
	{
	}
	int currChannel = tv.GetCurrChannel();
	BOOST_CHECK(currChannel == 0);

	tv.TurnOn();
	tv.SelectChannel(1);
	currChannel = tv.GetCurrChannel();
	BOOST_CHECK(currChannel == 1);

	tv.SelectChannel(99);
	currChannel = tv.GetCurrChannel();
	BOOST_CHECK(currChannel == 99);

	try
	{
		tv.SelectChannel(std::numeric_limits<unsigned>::max());
	}
	catch (const std::exception&)
	{
	}
	currChannel = tv.GetCurrChannel();
	BOOST_CHECK(currChannel == 99);

	tv.TurnOff();
	tv.TurnOn();
	currChannel = tv.GetCurrChannel();
	BOOST_CHECK(currChannel == 99);
}

BOOST_AUTO_TEST_CASE(testNameChannelSet) {
	CTVSet tv;

	std::string newName = "Different name";
	std::string newNameWithSpaces = " Different   name ";

	try
	{
		tv.SetChannelName(0, newName);
	}
	catch (const std::exception&)
	{
	}
	std::string currNullName = tv.GetCurrChannelName();
	BOOST_CHECK(currNullName.empty());

	tv.TurnOn();
	tv.SetChannelName(1, newName);
	std::string currName = tv.GetChannelName(1);
	BOOST_CHECK(currName == newName);

	tv.SetChannelName(1, newNameWithSpaces);
	currName = tv.GetChannelName(1);
	BOOST_CHECK(currName == newName);

	tv.SetChannelName(2, newName);
	currName = tv.GetChannelName(1);
	BOOST_CHECK(currName.empty());

	tv.DeleteChannelName(newName);
	currName = tv.GetChannelName(1);
	BOOST_CHECK(currName.empty());
}

BOOST_AUTO_TEST_CASE(testFindChannel) {
	CTVSet tv;
	tv.TurnOn();
	std::string name = "Channel name";

	tv.SetChannelName(1, name);
	tv.SelectChannel(2);
	tv.SelectChannel(name);
	BOOST_CHECK(tv.GetCurrChannel() == 1);
	BOOST_CHECK(tv.GetChannelByName(name) == 1);
	BOOST_CHECK(tv.GetChannelName(1) == name);
}

BOOST_AUTO_TEST_SUITE_END()