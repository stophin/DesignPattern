

#include "PolishNotation.h"


/*
*  �ж��ַ�op�Ƿ���������
*/
bool isValue(char op)
{
	//������ַ�Ϊ���ֻ��ַ���������ѹ��ջ
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
*  �ж��ַ�op�Ƿ��������
*/
bool isOperator(char op)
{
	return (op == '+') || (op == '-') || (op == '*') || (op == '/');
}

/*
*  ��ȡ����������ȼ�
*  +��- �� 2
*  *��/ �� 3
*  ���� �� 1
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
*  ��תһ���ַ�������ת��Ϊ��׺���ʽʱ�õ�
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
*  �������ܣ�����׺���ʽת��Ϊ��׺���ʽ
*  ������ expression: ��ת������׺���ʽ
*  ����ֵ�� �Ѿ�ת���õĺ�׺���ʽ
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
*  �������ܣ� ����׺���ʽת��Ϊǰ׺���ʽ
*  ������ expression: ��ת������׺���ʽ
*  ����ֵ�� �Ѿ�ת���õ�ǰ׺���ʽ
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