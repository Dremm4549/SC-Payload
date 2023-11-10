#include "pch.h"
#include "CppUnitTest.h"
#include "\Users\harri\Documents\Conestoga college\f23\project 5\SCPayload\SCPayload\source code\Packet.h"
#include "..\..\source code\Payload.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SCPayloadTests
{
	TEST_CLASS(SCPayloadTests)
	{
	public:
		

		TEST_METHOD(Test_Service_1_correct)
		{
			string expected = "1.2.3.4";
			Packet pack;
			pack.readIP();
			Assert::AreEqual(expected, pack.getIP(0));

		}

		TEST_METHOD(Test_Service_2_correct)
		{
			string expected = "5.6.7.8";
			Packet pack;
			pack.readIP();
			Assert::AreEqual(expected, pack.getIP(1));

		}

		TEST_METHOD(Test_Service_3_correct)
		{
			string expected = "9.10.11.12";
			Packet pack;
			pack.readIP();
			Assert::AreEqual(expected, pack.getIP(2));

		}

		TEST_METHOD(Test_Service_4_correct)
		{
			string expected = "13.14.15.16";
			Packet pack;
			pack.readIP();
			Assert::AreEqual(expected, pack.getIP(3));

		}

		TEST_METHOD(Test_Service_5_correct)
		{
			string expected = "17.18.19.20";
			Packet pack;
			pack.readIP();
			Assert::AreEqual(expected, pack.getIP(4));

		}

		TEST_METHOD(Test_Service_6_correct)
		{
			string expected = "21.22.23.24";
			Packet pack;
			pack.readIP();
			Assert::AreEqual(expected, pack.getIP(5));

		}

		TEST_METHOD(Test_Service_7_correct)
		{
			string expected = "25.26.27.28";
			Packet pack;
			pack.readIP();
			Assert::AreEqual(expected, pack.getIP(6));

		TEST_METHOD(SET_SATE_TEST_IS_GOOD)
		{
			Payload pay;
			pay.SetPowerState(true);
			Assert::IsTrue(pay.GetPowerState());
		}
		TEST_METHOD(SET_SATE_TEST_DEFAULT_CON)
		{
			Payload pay;
			Assert::IsFalse(pay.GetPowerState());
		}
		TEST_METHOD(SET_SATE_TEST_PARAM_CON_GOOD)
		{
			Payload pay(true);
			Assert::IsTrue(pay.GetPowerState());
		}
		TEST_METHOD(SET_SATE_TEST_PARAM_CON_BAD)
		{
			Payload pay(6);
			Assert::IsTrue(pay.GetPowerState());

		}
	};
}
