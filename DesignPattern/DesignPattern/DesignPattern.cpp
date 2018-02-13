// DesignPattern.cpp : 定义控制台应用程序的入口点。
//

#include "DesignPattern.h"

#include "SharedPtr.h"


void testSharedPtr() {
	shared_ptr<int> val(new int(100));
	printf("val=%d\n", *val);

	shared_ptr<int> temp(val);
	*temp = 300;
	printf("val=%d\n", *val);

	val = shared_ptr<int>(new int(200));
	printf("val=%d\n", *val);
}

#include "PrivateCreator.h"

void testPrivateCreator() {
	DemoClass * demo = DemoClass::MakeDemoClass();

	DemoClass _demo();

	demo->Release();
}

#include "Expression.h"

void testExpression() {
	Calculator::test();
}

#include "RobotControl.h"

void testRobotControl() {
	InstructionHandler::test();
}

int main(int argc, char* argv[])
{
	testSharedPtr();

	testPrivateCreator();

	testExpression();

	testRobotControl();

	getch();

	return 0;
}

