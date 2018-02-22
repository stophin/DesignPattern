
#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include "DesignPattern.h"

//解释器模式
//抽象表达式类
class Expression {
public:
	//解析公式的数值，其中var中的key是公式中的参数，value值是具体的数字
	virtual int interpreter(map<string, int>& var) = 0;
	virtual ~Expression() {};
};

//变量解析器（终结符表达式）
class VarExpression : public Expression {
	string key;
public:
	VarExpression(string key) {
		this->key = key;
	}

	//从map中取出变量的值
	virtual int interpreter(map<string, int>& var) {
		return var[key];
	}
	~VarExpression() {
		cout << "~VarExpression()" << endl;
	}
};

//抽象运算符解析器
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

//加法解释器
class AddExpression : public SymbolExpression {
public:
	AddExpression(Expression * left, Expression * right) :
		SymbolExpression(left, right) {

	}
	//把左右两个表达式运算的结果加起来
	virtual int interpreter(map<string, int>& var) {
		return left->interpreter(var) + right->interpreter(var);
	}
	~AddExpression() {
		cout << "~AddExpression()" << endl;
	}
};

//减法解释器
class SubExpression : public SymbolExpression {
public:
	SubExpression(Expression * left, Expression * right) :
		SymbolExpression(left, right) {

	}
	//把左右两个表达式运算的结果相减
	virtual int interpreter(map<string, int>& var) {
		return left->interpreter(var) - right->interpreter(var);
	}
	~SubExpression() {
		cout << "~SubExpression()" << endl;
	}
};
//乘法解释器
class MulExpression : public SymbolExpression {
public:
	MulExpression(Expression * left, Expression * right) :
		SymbolExpression(left, right) {

	}
	//把左右两个表达式运算的结果相乘
	virtual int interpreter(map<string, int>& var) {
		return left->interpreter(var) * right->interpreter(var);
	}
	~MulExpression() {
		cout << "~MulExpression()" << endl;
	}
};
//除法解释器
class DivExpression : public SymbolExpression {
public:
	DivExpression(Expression * left, Expression * right) :
		SymbolExpression(left, right) {

	}
	//把左右两个表达式运算的结果相除
	virtual int interpreter(map<string, int>& var) {
		return left->interpreter(var) / right->interpreter(var);
	}
	~DivExpression() {
		cout << "~DivExpression()" << endl;
	}
};

//解析器封装类
//根据迪米特法则进行封装，目的是让Client至于直接朋友打交道，相当于Facade
class Calculator {
private :
	Expression * expression;
public:
	//解析构造语法树
	Calculator(string expStr) {
		expression = NULL;

		//栈，用来暂存中间结果
		stack<Expression*> expStk;

		Expression * left = NULL;
		Expression * right = NULL;

		//从左到右分析表达式（如a+b-c)，构造如下语法树
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
				//从栈中取出左操作数
				left = expStk.top();
				expStk.pop();
				//从表达式中取出+号后面的右操作数，并生成终结符解析对象
				right = new VarExpression(expStr.substr(++i, 1));
				//将左右操作数相加，并把结果放入栈中
				expStk.push(new AddExpression(left, right));
				break;
			case '-':
				//从栈中取出左操作数
				left = expStk.top();
				expStk.pop();
				//从表达式中取出-号后面的右操作数，并生成终结符解析对象
				right = new VarExpression(expStr.substr(++i, 1));
				//将左右操作数相减，并把结果放入栈中
				expStk.push(new SubExpression(left, right));
				break;
			case '*':
				//从栈中取出左操作数
				left = expStk.top();
				expStk.pop();
				//从表达式中取出-号后面的右操作数，并生成终结符解析对象
				right = new VarExpression(expStr.substr(++i, 1));
				//将左右操作数相乘，并把结果放入栈中
				expStk.push(new MulExpression(left, right));
				break;
			default:
				//如果是变量（终结符，如a+b+c中的a、b或c）
				//则直接生成对应的变量解析器对象
				expStk.push(new VarExpression(expStr.substr(i, 1)));
			}
		}
		//栈中保存的就是最终语法树的根节点
		if (!expStk.empty()) {
			expression = expStk.top();
			expStk.pop();
		}
	}


	//解析构造语法树
	Calculator(string expStr, int type) {
		expression = NULL;

		//栈，用来暂存中间结果
		stack<Expression*> expStk;

		Expression * left = NULL;
		Expression * right = NULL;

		//分析逆波兰式（ab+c*)，构造如下语法树
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
				//从栈中取出右操作数
				right = expStk.top();
				expStk.pop();
				//从栈中取出左操作数
				left = expStk.top();
				expStk.pop();
				//将左右操作数相加，并把结果放入栈中
				expStk.push(new AddExpression(left, right));
				break;
			case '-':
				//从栈中取出右操作数
				right = expStk.top();
				expStk.pop();
				//从栈中取出左操作数
				left = expStk.top();
				expStk.pop();
				//将左右操作数相减，并把结果放入栈中
				expStk.push(new SubExpression(left, right));
				break;
			case '*':
				//从栈中取出右操作数
				right = expStk.top();
				expStk.pop();
				//从栈中取出左操作数
				left = expStk.top();
				expStk.pop();
				//将左右操作数相乘，并把结果放入栈中
				expStk.push(new MulExpression(left, right));
				break;
			case '/':
				//从栈中取出右操作数
				right = expStk.top();
				expStk.pop();
				//从栈中取出左操作数
				left = expStk.top();
				expStk.pop();
				//将左右操作数相除，并把结果放入栈中
				expStk.push(new DivExpression(left, right));
				break;
			default:
				//如果是变量（终结符，如a+b+c中的a、b或c）
				//则直接生成对应的变量解析器对象
				expStk.push(new VarExpression(expStr.substr(i, 1)));
			}
		}
		//栈中保存的就是最终语法树的根节点
		if (!expStk.empty()) {
			expression = expStk.top();
			expStk.pop();
		}
	}

	void delTree(Expression * expression) {
		SymbolExpression * branch = dynamic_cast<SymbolExpression*>(expression);

		if (branch == NULL) {
			//叶子节点
			//delete expression;
		}
		else {
			//分支节点
			//左子树
			delTree(branch->getLeft());
			//右子树
			delTree(branch->getRight());
			//节点
			delete expression;

		}
	}

	~Calculator() {
		delTree(expression);
		expression = NULL;
		cout << "~Calculator()" << endl;
	}

	//开始运算
	int run(map<string, int>& var) {
		return (expression == NULL) ? 0 : expression->interpreter(var);
	}

	static void test() {
		//保证是合法表达式
		
		/*
		注：
		中缀表达式也就是人类经常使用的表达式，一般使用括号和运算符号来表达运算顺序
		前缀表达式，也叫波兰式，表达式一般为“操作符,操作数1，操作数2”
		后缀表达式，也叫逆波兰式，表达式一般为“操作数1，操作数2，操作符”
		*/

		//使用中缀表达式
		string expStr = "a+b-c";

		map<string, int> var;//相当于Interpreter模式中的Context
		var["a"] = 100;
		var["b"] = 20;
		var["c"] = 40;

		Calculator cal(expStr);

		cout << "运算结果为：" << expStr.c_str() << "=" << cal.run(var) << endl;

		//但是对于中缀表达式不能处理运算顺序
		string expStr_1 = "a+b*c";
		Calculator cal_1(expStr_1);
		cout << "运算结果为：（错误的结果）" << expStr_1.c_str() << "=" << cal_1.run(var) << endl;

		//也可以是后缀逆波兰式
		//a+b*c-c
		string expStr1 = "ab+c*c-";
		Calculator cal1(expStr1, 1);
		cout << "运算结果为：" << expStr1.c_str() << "=" << cal1.run(var) << endl;

		//后缀逆波兰式可以很好地解决运算顺序问题
		//(a+b)*c-(a+b)/e
		string expStr2 = "ab+c*ab+e/-";
		var["d"] = 100;
		var["e"] = 20;
		Calculator cal2(expStr2, 1);
		cout << "运算结果为：" << expStr2.c_str() << "=" << cal2.run(var) << endl;

		//a - b * c
		string expStr3 = "abc*-";
		Calculator cal3(expStr3, 1);
		cout << "运算结果为：" << expStr3.c_str() << "=" << cal3.run(var) << endl;

		//(a - b) * c
		string expStr4 = "ab-c*";
		Calculator cal4(expStr4, 1);
		cout << "运算结果为：" << expStr4.c_str() << "=" << cal4.run(var) << endl;

		// a + b * (c - d) / e
		string expStr5 = "abcd-*e/+";
		Calculator cal5(expStr5, 1);
		cout << "运算结果为：" << expStr5.c_str() << "=" << cal5.run(var) << endl;
	}
};

#endif