#pragma once
#include "pch.h"
#include "../TV/Channel.h"
#include "../TV/CTVSet.h"

#define BOOST_TEST_MODULE TvTest
#include <boost/test/unit_test.hpp>

struct TVFixture
{
	CTVSet tv;
};

BOOST_FIXTURE_TEST_SUITE(tvTest, TVFixture)
		
	BOOST_AUTO_TEST_SUITE(testTvCreation)

		BOOST_AUTO_TEST_CASE(testTurnOff)
		{
			BOOST_CHECK_THROW(tv.TurnOff(), std::exception);
		}

		BOOST_AUTO_TEST_CASE(tesTurnedOfftTvValues) 
		{
			BOOST_CHECK(tv.GetCurrChannel() == 0);
			BOOST_CHECK(tv.GetCurrChannelName().empty());
		}

		BOOST_AUTO_TEST_CASE(testTurnedOffTvCommands)
		{
			BOOST_CHECK_THROW(tv.SelectChannel(56), std::exception);
			BOOST_CHECK_THROW(tv.SelectChannel("Name"), std::exception);
			BOOST_CHECK_THROW(tv.SetChannelName(0, "Name"), std::exception);
			BOOST_CHECK_THROW(tv.SetChannelName(23, "Name"), std::exception);
			BOOST_CHECK_THROW(tv.SelectPreviousChannel(), std::exception);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct TVTurnedOnFixture : TVFixture
	{
		TVTurnedOnFixture() 
		{
			tv.TurnOn();
		}
	};
	BOOST_FIXTURE_TEST_SUITE(testTurnedOnTV, TVTurnedOnFixture)

		BOOST_AUTO_TEST_CASE(testTurnOn)
		{
			BOOST_CHECK_THROW(tv.TurnOn(), std::exception);
		}
	
		BOOST_AUTO_TEST_CASE(testTurnOff)
		{
			tv.SelectChannel(2);
			tv.TurnOff();
			tv.TurnOn();
			BOOST_CHECK(tv.GetCurrChannel() == 2);
		}

		BOOST_AUTO_TEST_CASE(testTurnedOnTvValues)
		{
			BOOST_CHECK(tv.GetCurrChannel() == 1);
			BOOST_CHECK(tv.GetCurrChannelName().empty());
		}		

		BOOST_AUTO_TEST_SUITE(testTvSelectChannel)

			BOOST_AUTO_TEST_CASE(testTvSelectChannel1)
			{
				tv.SelectChannel(22);
				BOOST_CHECK(tv.GetCurrChannel() == 22);
			}
			
			BOOST_AUTO_TEST_CASE(testTvSelectCurrentChannel)
			{
				tv.SelectChannel(1);
				BOOST_CHECK(tv.GetCurrChannel() == 1);
			}
			
			BOOST_AUTO_TEST_CASE(testTvSelectSignedChannel)
			{
				BOOST_CHECK_THROW(tv.SelectChannel(-12), std::exception);
				BOOST_CHECK(tv.GetCurrChannel() == 1);
			}
			
			BOOST_AUTO_TEST_CASE(testTvSelectOutOfRangeChannel)
			{
				BOOST_CHECK_THROW(tv.SelectChannel(std::numeric_limits<unsigned>().max()), std::exception);
				BOOST_CHECK(tv.GetCurrChannel() == 1);
			}
			
			BOOST_AUTO_TEST_CASE(testTvSelectPreviousChannelAfterTurnOn)
			{
				tv.SelectPreviousChannel();
				BOOST_CHECK(tv.GetCurrChannel() == 1);
			}
			
			BOOST_AUTO_TEST_CASE(testTvSelectPreviousChannel)
			{
				tv.SelectChannel(2);
				tv.SelectPreviousChannel();
				BOOST_CHECK(tv.GetCurrChannel() == 1);
			}

		BOOST_AUTO_TEST_SUITE_END()


		BOOST_AUTO_TEST_SUITE(testTvSetNames)

			BOOST_AUTO_TEST_CASE(testTvSetDefaultName)
			{
				tv.SetChannelName(1, "Simple Name");
				BOOST_CHECK(tv.GetCurrChannelName() == "Simple Name");
			}

			BOOST_AUTO_TEST_CASE(testTvSetNamesSpaces)
			{
				tv.SetChannelName(1, "   Not Simple     Name   ");
				BOOST_CHECK(tv.GetCurrChannelName() == "Not Simple Name");
			}

		BOOST_AUTO_TEST_SUITE_END()
		
		struct TvWithNames : TVTurnedOnFixture
		{
			TvWithNames()
			{
				tv.SetChannelName(1, "First Channel");
				tv.SetChannelName(2, "Second Channel");
			}
		};
		BOOST_FIXTURE_TEST_SUITE(testTvWithNames, TvWithNames)

			BOOST_AUTO_TEST_SUITE(testSwapChannelName)

				BOOST_AUTO_TEST_CASE(testSwapChannelName1)
				{
					tv.SetChannelName(3, "First Channel");
					BOOST_CHECK(tv.GetChannelName(3) == "First Channel");
					BOOST_CHECK(tv.GetChannelName(1).empty());
				}

				BOOST_AUTO_TEST_CASE(testSwapChannelName2)
				{
					tv.SetChannelName(2, "First Channel");
					BOOST_CHECK(tv.GetChannelName(2) == "First Channel");
					BOOST_CHECK(tv.GetChannelName(1) == "Second Channel");
				}

				BOOST_AUTO_TEST_CASE(testTvSetEmptyName)
				{
					BOOST_CHECK_THROW(tv.SetChannelName(1, ""), std::exception);
					BOOST_CHECK(tv.GetChannelName(1) == "First Channel");
				}
				
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_AUTO_TEST_SUITE(testSelectChanneByName)

				BOOST_AUTO_TEST_CASE(testSelectChanneByName1)
				{
					tv.SelectChannel("Second Channel");
					BOOST_CHECK(tv.GetCurrChannel() == 2);
				}
				
				BOOST_AUTO_TEST_CASE(testSelectChanneByName2)
				{
					BOOST_CHECK_THROW(tv.SelectChannel(""), std::exception);
					BOOST_CHECK(tv.GetCurrChannel() == 1);
				}

			BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
