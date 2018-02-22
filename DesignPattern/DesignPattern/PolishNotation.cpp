

#include "PolishNotation.h"


/*
*  判断字符op是否是运算数
*/
bool isValue(char op)
{
	//如果该字符为数字或字符，解析并压入栈
	if (op >= '0' && op <= '9') {
		return true;
	}
	else if ((op >= 'a' && op <= 'z') ||
		(op >= 'A' && op <= 'Z')) {
		return true;
	}
	return false;
}


/*
*  判断字符op是否是运算符
*/
bool isOperator(char op)
{
	return (op == '+') || (op == '-') || (op == '*') || (op == '/');
}

/*
*  获取运算符的优先级
*  +或- ： 2
*  *或/ ： 3
*  其它 ： 1
*/
int getPriority(char op)
{
	switch (op) {
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	default:
		return 1;
	}
}

/*
*  反转一个字符串，在转换为后缀表达式时用到
*/
void reverseStr(char *str)
{
	int i = 0;
	int j = strlen(str) - 1;
	char temp;
	while (i<j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

class MyStack : public stack<char> {
public:
	MyStack(int l, int t) {

	}

	bool getTopElement(char& e) {
		if (empty()) {
			return false;
		}
		else {
			e = stack<char>::top();
			return true;
		}
	}

	bool pop(char& e) {
		if (empty()) {
			return false;
		}
		else {
			e = stack<char>::top();
			stack<char>::pop();
			return true;
		}
	}
};

/*
*  函数功能：将中缀表达式转换为后缀表达式
*  参数： expression: 待转换的中缀表达式
*  返回值： 已经转换好的后缀表达式
*/
char * toReversePolishNotation(const char * expression, char * result)
{
	if (expression == NULL) {
		return NULL;
	}
	if (result == NULL) {
		return NULL;
	}
	int length = strlen(expression);
	MyStack opStack(length, 0);
	MyStack tempStack(length, 0);
	//char * result = (char *)malloc(sizeof(char)* (length + 1));
	const char * pstr = expression;
	char e, topE;
	int i = 0;

	while (*pstr) {
		if (isValue(*pstr)) {
			tempStack.push(*pstr);
		}
		else if (isOperator(*pstr)) {
			while (opStack.getTopElement(topE)) {
				if ((topE == '(') || (getPriority(*pstr)>getPriority(topE)))
					break;
				opStack.pop(e);
				tempStack.push(e);
			}
			opStack.push(*pstr);
		}
		else if (*pstr == '(') {
			opStack.push(*pstr);
		}
		else if (*pstr == ')') {
			while (opStack.pop(e)) {
				if (e == '(')
					break;
				tempStack.push(e);
			}
		}
		pstr++;
	}
	while (opStack.pop(e)) {
		tempStack.push(e);
	}

	while (tempStack.pop(e)) {
		result[i] = e;
		i++;
	}
	result[i] = '\0';
	reverseStr(result);

	return result;

}

/*
*  函数功能： 将中缀表达式转换为前缀表达式
*  参数： expression: 待转换的中缀表达式
*  返回值： 已经转换好的前缀表达式
*/
char * toPolishNotation(const char * expression, char * result)
{
	if (expression == NULL)
		return NULL;
	int length = strlen(expression);
	MyStack opStack(length, 0);
	MyStack tempStack(length, 0);
	//char * result = (char *)malloc((length + 1) * sizeof(char));
	char e, topE;
	int i = 0;
	int index = length - 1;

	while (index >= 0) {
		if (isValue(expression[index])) {
			tempStack.push(expression[index]);
		}
		else if (isOperator(expression[index])) {
			while (opStack.getTopElement(topE)) {
				if ((topE == ')') || (getPriority(expression[index]) >= getPriority(topE)))
					break;
				opStack.pop(e);
				tempStack.push(e);
			}
			opStack.push(expression[index]);
		}
		else if (expression[index] == ')') {
			opStack.push(expression[index]);
		}
		else if (expression[index] == '(') {
			while (opStack.pop(e)) {
				if (e == ')')
					break;
				tempStack.push(e);
			}
		}
		index--;
	}

	while (opStack.pop(e)) {
		tempStack.push(e);
	}

	while (tempStack.pop(e)) {
		result[i] = e;
		i++;
	}
	result[i] = '\0';

	return result;
}