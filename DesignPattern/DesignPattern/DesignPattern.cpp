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
#include "RobotControl.h"

void testRobotControl() {
	InstructionHandler::test();
}

#include "PolishNotation.h"

void testPolishNotation() {
	const char * exp = "3+(2-5)";

	char buf[100];

	char * result;
	result = toPolishNotation(exp, buf);
	printf("����ʽ��\t%s\n", result);

	result = toReversePolishNotation(exp, buf);
	printf("�沨��ʽ��\t%s\n", result);
}

#include "Expression.h"

void testExpression() {
	Calculator::test();

	map<string, int> var;
	var["a"] = 100;
	var["b"] = 20;
	var["c"] = 40;
	var["d"] = 100;
	var["e"] = 20;

	{
		//a+b*c-c
		const char * exp = "a+b*c-c";
		printf("����ʽ��\t%s\n", exp);
		//ʹ���沨��ʽ���ɣ�����expression����
		char buff[100];
		char * result;
		result = toReversePolishNotation(exp, buff);
		printf("�沨��ʽ��\t%s\n", result);
		//�����沨��ʽ
		string expStr(result);
		Calculator cal(expStr, 1);
		cout << "������Ϊ��\t" << expStr.c_str() << "=" << cal.run(var) << endl;
	}
	{
		//(a+b)*c-(a+b)/e
		const char * exp = "(a+b)*c-(a+b)/e";
		printf("����ʽ��\t%s\n", exp);
		//ʹ���沨��ʽ���ɣ�����expression����
		char buff[100];
		char * result;
		result = toReversePolishNotation(exp, buff);
		printf("�沨��ʽ��\t%s\n", result);
		//�����沨��ʽ
		string expStr(result);
		Calculator cal(expStr, 1);
		cout << "������Ϊ��\t" << expStr.c_str() << "=" << cal.run(var) << endl;
	}
	{
		//a - b * c
		const char * exp = "a - b * c";
		printf("����ʽ��\t%s\n", exp);
		//ʹ���沨��ʽ���ɣ�����expression����
		char buff[100];
		char * result;
		result = toReversePolishNotation(exp, buff);
		printf("�沨��ʽ��\t%s\n", result);
		//�����沨��ʽ
		string expStr(result);
		Calculator cal(expStr, 1);
		cout << "������Ϊ��\t" << expStr.c_str() << "=" << cal.run(var) << endl;
	}
	{
		//(a - b) * c
		const char * exp = "(a - b) * c";
		printf("����ʽ��\t%s\n", exp);
		//ʹ���沨��ʽ���ɣ�����expression����
		char buff[100];
		char * result;
		result = toReversePolishNotation(exp, buff);
		printf("�沨��ʽ��\t%s\n", result);
		//�����沨��ʽ
		string expStr(result);
		Calculator cal(expStr, 1);
		cout << "������Ϊ��\t" << expStr.c_str() << "=" << cal.run(var) << endl;
	}
	{
		//a + b * (c - d) / e
		const char * exp = "a + b * (c - d) / e";
		printf("����ʽ��\t%s\n", exp);
		//ʹ���沨��ʽ���ɣ�����expression����
		char buff[100];
		char * result;
		result = toReversePolishNotation(exp, buff);
		printf("�沨��ʽ��\t%s\n", result);
		//�����沨��ʽ
		string expStr(result);
		Calculator cal(expStr, 1);
		cout << "������Ϊ��\t" << expStr.c_str() << "=" << cal.run(var) << endl;
	}
}

#include "TemplateCast.h"

void testTemplateCast() {
	Template_Cast::test();

	Template_Loop::test();
}

#include "AutoPtr.h"

void testAutoPtr() {
	Auto_Ptr::test();
}



int main(int argc, char* argv[])
{
	testSharedPtr();

	testPrivateCreator();

	testRobotControl();

	testPolishNotation();
	testExpression();

	testTemplateCast();

	testAutoPtr();

	getch();

	return 0;
}

