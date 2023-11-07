#include "pch.h"
#include "CppUnitTest.h"
#include "..\..\source code\Payload.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SCPayloadTests
{
	TEST_CLASS(SCPayloadTests)
	{
	public:
		
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
