// DesignPattern.cpp : �������̨Ӧ�ó������ڵ㡣
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

int main(int argc, char* argv[])
{
	testSharedPtr();

	testPrivateCreator();

	testExpression();

	getch();

	return 0;
}

