
#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include "DesignPattern.h"

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
//����������
class DivExpression : public SymbolExpression {
public:
	DivExpression(Expression * left, Expression * right) :
		SymbolExpression(left, right) {

	}
	//�������������ʽ����Ľ�����
	virtual int interpreter(map<string, int>& var) {
		return left->interpreter(var) / right->interpreter(var);
	}
	~DivExpression() {
		cout << "~DivExpression()" << endl;
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
			case '/':
				//��ջ��ȡ���Ҳ�����
				right = expStk.top();
				expStk.pop();
				//��ջ��ȡ���������
				left = expStk.top();
				expStk.pop();
				//�����Ҳ�������������ѽ������ջ��
				expStk.push(new DivExpression(left, right));
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
		//��֤�ǺϷ����ʽ
		
		/*
		ע��
		��׺���ʽҲ�������ྭ��ʹ�õı��ʽ��һ��ʹ�����ź�����������������˳��
		ǰ׺���ʽ��Ҳ�в���ʽ�����ʽһ��Ϊ��������,������1��������2��
		��׺���ʽ��Ҳ���沨��ʽ�����ʽһ��Ϊ��������1��������2����������
		*/

		//ʹ����׺���ʽ
		string expStr = "a+b-c";

		map<string, int> var;//�൱��Interpreterģʽ�е�Context
		var["a"] = 100;
		var["b"] = 20;
		var["c"] = 40;

		Calculator cal(expStr);

		cout << "������Ϊ��" << expStr.c_str() << "=" << cal.run(var) << endl;

		//���Ƕ�����׺���ʽ���ܴ�������˳��
		string expStr_1 = "a+b*c";
		Calculator cal_1(expStr_1);
		cout << "������Ϊ��������Ľ����" << expStr_1.c_str() << "=" << cal_1.run(var) << endl;

		//Ҳ�����Ǻ�׺�沨��ʽ
		//a+b*c-c
		string expStr1 = "ab+c*c-";
		Calculator cal1(expStr1, 1);
		cout << "������Ϊ��" << expStr1.c_str() << "=" << cal1.run(var) << endl;

		//��׺�沨��ʽ���Ժܺõؽ������˳������
		//(a+b)*c-(a+b)/e
		string expStr2 = "ab+c*ab+e/-";
		var["d"] = 100;
		var["e"] = 20;
		Calculator cal2(expStr2, 1);
		cout << "������Ϊ��" << expStr2.c_str() << "=" << cal2.run(var) << endl;

		//a - b * c
		string expStr3 = "abc*-";
		Calculator cal3(expStr3, 1);
		cout << "������Ϊ��" << expStr3.c_str() << "=" << cal3.run(var) << endl;

		//(a - b) * c
		string expStr4 = "ab-c*";
		Calculator cal4(expStr4, 1);
		cout << "������Ϊ��" << expStr4.c_str() << "=" << cal4.run(var) << endl;

		// a + b * (c - d) / e
		string expStr5 = "abcd-*e/+";
		Calculator cal5(expStr5, 1);
		cout << "������Ϊ��" << expStr5.c_str() << "=" << cal5.run(var) << endl;
	}
};

#endif