
#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include "DesignPattern.h"

#include <map>
#include <stack>
#include <typeinfo>
#include <iostream>
using namespace std;

//������ģʽ
//������ʽ��
class Expression {
public:
	//������ʽ����ֵ������var�е�key�ǹ�ʽ�еĲ�����valueֵ�Ǿ��������
	virtual int interpreter(map<string, int>& var) = 0;
	virtual ~Expression() {};
};

//�������������ս�����ʽ��
class VarExpression : public Expression {
	string key;
public:
	VarExpression(string key) {
		this->key = key;
	}

	//��map��ȡ��������ֵ
	virtual int interpreter(map<string, int>& var) {
		return var[key];
	}
	~VarExpression() {
		cout << "~VarExpression()" << endl;
	}
};

//���������������
class SymbolExpression : public Expression {
protected:
	Expression * left;
	Expression * right;
public:
	SymbolExpression(Expression * left, Expression * right) {
		this->left = left;
		this->right = right;
	}

	Expression * getLeft() {
		return left;
	}
	Expression * getRight() {
		return right;
	}
};

//�ӷ�������
class AddExpression : public SymbolExpression {
public:
	AddExpression(Expression * left, Expression * right) :
		SymbolExpression(left, right) {

	}
	//�������������ʽ����Ľ��������
	virtual int interpreter(map<string, int>& var) {
		return left->interpreter(var) + right->interpreter(var);
	}
	~AddExpression() {
		cout << "~AddExpression()" << endl;
	}
};

//����������
class SubExpression : public SymbolExpression {
public:
	SubExpression(Expression * left, Expression * right) :
		SymbolExpression(left, right) {

	}
	//�������������ʽ����Ľ�����
	virtual int interpreter(map<string, int>& var) {
		return left->interpreter(var) - right->interpreter(var);
	}
	~SubExpression() {
		cout << "~SubExpression()" << endl;
	}
};
//�˷�������
class MulExpression : public SymbolExpression {
public:
	MulExpression(Expression * left, Expression * right) :
		SymbolExpression(left, right) {

	}
	//�������������ʽ����Ľ�����
	virtual int interpreter(map<string, int>& var) {
		return left->interpreter(var) * right->interpreter(var);
	}
	~MulExpression() {
		cout << "~MulExpression()" << endl;
	}
};

//��������װ��
//���ݵ����ط�����з�װ��Ŀ������Client����ֱ�����Ѵ򽻵����൱��Facade
class Calculator {
private :
	Expression * expression;
public:
	//���������﷨��
	Calculator(string expStr) {
		expression = NULL;

		//ջ�������ݴ��м���
		stack<Expression*> expStk;

		Expression * left = NULL;
		Expression * right = NULL;

		//�����ҷ������ʽ����a+b-c)�����������﷨��
		/*
		 *           -
         *         /   \
         *       +     c
         *     /   \
         *    a     b
        */
		unsigned int len = expStr.length();
		for (unsigned int i = 0; i < len; i++) {
			switch (expStr[i]) {
			case '+':
				//��ջ��ȡ���������
				left = expStk.top();
				expStk.pop();
				//�ӱ��ʽ��ȡ��+�ź�����Ҳ��������������ս����������
				right = new VarExpression(expStr.substr(++i, 1));
				//�����Ҳ�������ӣ����ѽ������ջ��
				expStk.push(new AddExpression(left, right));
				break;
			case '-':
				//��ջ��ȡ���������
				left = expStk.top();
				expStk.pop();
				//�ӱ��ʽ��ȡ��-�ź�����Ҳ��������������ս����������
				right = new VarExpression(expStr.substr(++i, 1));
				//�����Ҳ�������������ѽ������ջ��
				expStk.push(new SubExpression(left, right));
				break;
			case '*':
				//��ջ��ȡ���������
				left = expStk.top();
				expStk.pop();
				//�ӱ��ʽ��ȡ��-�ź�����Ҳ��������������ս����������
				right = new VarExpression(expStr.substr(++i, 1));
				//�����Ҳ�������ˣ����ѽ������ջ��
				expStk.push(new MulExpression(left, right));
				break;
			default:
				//����Ǳ������ս������a+b+c�е�a��b��c��
				//��ֱ�����ɶ�Ӧ�ı�������������
				expStk.push(new VarExpression(expStr.substr(i, 1)));
			}
		}
		//ջ�б���ľ��������﷨���ĸ��ڵ�
		if (!expStk.empty()) {
			expression = expStk.top();
			expStk.pop();
		}
	}


	//���������﷨��
	Calculator(string expStr, int type) {
		expression = NULL;

		//ջ�������ݴ��м���
		stack<Expression*> expStk;

		Expression * left = NULL;
		Expression * right = NULL;

		//�����沨��ʽ��ab+c*)�����������﷨��
		/*
		*           -
		*         /   \
		*       +     c
		*     /   \
		*    a     b
		*/
		unsigned int len = expStr.length();
		for (unsigned int i = 0; i < len; i++) {
			switch (expStr[i]) {
			case '+':
				//��ջ��ȡ���Ҳ�����
				right = expStk.top();
				expStk.pop();
				//��ջ��ȡ���������
				left = expStk.top();
				expStk.pop();
				//�����Ҳ�������ӣ����ѽ������ջ��
				expStk.push(new AddExpression(left, right));
				break;
			case '-':
				//��ջ��ȡ���Ҳ�����
				right = expStk.top();
				expStk.pop();
				//��ջ��ȡ���������
				left = expStk.top();
				expStk.pop();
				//�����Ҳ�������������ѽ������ջ��
				expStk.push(new SubExpression(left, right));
				break;
			case '*':
				//��ջ��ȡ���Ҳ�����
				right = expStk.top();
				expStk.pop();
				//��ջ��ȡ���������
				left = expStk.top();
				expStk.pop();
				//�����Ҳ�������ˣ����ѽ������ջ��
				expStk.push(new MulExpression(left, right));
				break;
			default:
				//����Ǳ������ս������a+b+c�е�a��b��c��
				//��ֱ�����ɶ�Ӧ�ı�������������
				expStk.push(new VarExpression(expStr.substr(i, 1)));
			}
		}
		//ջ�б���ľ��������﷨���ĸ��ڵ�
		if (!expStk.empty()) {
			expression = expStk.top();
			expStk.pop();
		}
	}

	void delTree(Expression * expression) {
		SymbolExpression * branch = dynamic_cast<SymbolExpression*>(expression);

		if (branch == NULL) {
			//Ҷ�ӽڵ�
			//delete expression;
		}
		else {
			//��֧�ڵ�
			//������
			delTree(branch->getLeft());
			//������
			delTree(branch->getRight());
			//�ڵ�
			delete expression;

		}
	}

	~Calculator() {
		delTree(expression);
		expression = NULL;
		cout << "~Calculator()" << endl;
	}

	//��ʼ����
	int run(map<string, int>& var) {
		return (expression == NULL) ? 0 : expression->interpreter(var);
	}

	static void test() {
		//��֤�ǺϷ����ʽ�����Ѿ�������������������
		//������(a+b)*c�Ĺ��������ı��ʽ
		string expStr = "a+b-c";

		map<string, int> var;//�൱��Interpreterģʽ�е�Context
		var["a"] = 100;
		var["b"] = 20;
		var["c"] = 40;

		Calculator cal(expStr);

		cout << "������Ϊ��" << expStr.c_str() << "=" << cal.run(var) << endl;

		//Ҳ�������沨��ʽ
		string expStr1 = "ab+c*c-";
		Calculator cal1(expStr1, 1);
		cout << "������Ϊ��" << expStr1.c_str() << "=" << cal1.run(var) << endl;
	}
};

#endif