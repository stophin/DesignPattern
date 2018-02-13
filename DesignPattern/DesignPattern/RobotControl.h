//行为型模式：解释器模式
//场景：开发一套机器人控制程序
/*说明：
机器人控制程序中包含一些简单的英文控制指令，每一个指令对应一个表达式(expression)，
该表达式可以是简单表达式也可以是复合表达式，每一个简单表达式由移动方向(direction)，
移动方式(action)和移动距离(distance)三部分组成，其中移动方向包括上(up)、下(down)、
左(left)、右(right)；移动方式包括移动(move)和快速移动(run)；移动距离为一个正整数。
两个表达式之间可以通过与(and)连接，形成复合(composite)表达式。
用户通过对图形化的设置界面进行操作可以创建一个机器人控制指令，机器人在收到指令
后将按照指令的设置进行移动，例如输入控制指令：up move 5，则“向上移动5个单位”；输入控
制指令：down  run 10 and left move 20，则“向下快速移动10个单位再向左移动20个单位”。
*/

/*文法规则
expression ::= direction action distance | composite //表达式
composite ::= expression 'and' expression //复合表达式
direction ::= 'up' | 'down' | 'left' | 'right' //移动方向
action ::= 'move' | 'run' //移动方式
distance ::= an integer //移动距离
上述语言一共定义了五条文法规则，对应五个语言单位，这些语言单位可以分为两类，
终结符（也称为终结符表达式）：例如direction、action和distance，它们是语言的最小组成单位，不能再进行拆分；
非终结符（也称为非终结符表达式），例如expression和composite，它们都是一个完整的句子，包含一系列终结符或非终结符。
*/

//本实例对机器人控制指令的输出结果进行模拟，将英文指令翻译为中文指令，实际情况是调用不同的控制程序进行机器人的控制，
//包括对移动方向、方式和距离的控制等
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <typeinfo>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// 字符串分割
//
// -------------------------------------------------------------------------
// 函数     : Split
// 功能     : 分割STL标准字符串
// 返回值   : void
// 参数     : Container<std::basic_string<CharT> >& v 存放分割结果
// 参数     : const std::basic_string<CharT>& s 待分割字符串
// 参数     : const std::basic_string<CharT>& c 分割字符串
// -------------------------------------------------------------------------
template<typename CharT, template<typename S, typename Q = std::allocator<S> > class Container>
void Split(Container<std::basic_string<CharT> >& v, const std::basic_string<CharT>& s, const std::basic_string<CharT>& c);

template<template<typename S, typename Q = std::allocator<S> > class Container>
void Split(Container<std::basic_string<char> >& v, const std::basic_string<char>& s, const std::basic_string<char>& c)
{
	if (0 == c.length())
		return;

	std::basic_string<char>::size_type pos1 = 0;
	std::basic_string<char>::size_type pos2 = 0;

	pos1 = 0;
	pos2 = s.find(c);
	while (std::basic_string<char>::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}

	if (pos1 != s.length())
	{
		v.push_back(s.substr(pos1));
	}
}

//抽象类：解释器
class AbstractExpression
{
public:
	virtual string interpret() = 0;
	virtual ~AbstractExpression(){}
};
//And解释器：非终结符表达式
class AndExpression : public AbstractExpression
{
private:
	AbstractExpression* left; //And的左表达式
	AbstractExpression* right; //And的右表达式
public:
	AndExpression(AbstractExpression* left,
		AbstractExpression* right)
	{
		this->left = left;
		this->right = right;
	}

	//And表达式解释操作
	string interpret()
	{
		return left->interpret() + "再" + right->interpret();
	}

	AbstractExpression* getLeft()
	{
		return left;
	}

	AbstractExpression* getRight()
	{
		return right;
	}
};

//简单句子解释器：非终结符表达式
//如：up move 5，表示“向上移动5个单位
class SentenceExpression : public AbstractExpression
{
private:
	AbstractExpression* direction;
	AbstractExpression* action;
	AbstractExpression* distance;
public:
	SentenceExpression(AbstractExpression* direction,
		AbstractExpression* action,
		AbstractExpression* distance)
	{
		this->direction = direction;
		this->action = action;
		this->distance = distance;
	}

	//解释操作
	string interpret()
	{
		return direction->interpret() + action->interpret() + distance->interpret();
	}

	AbstractExpression* getDirection()
	{
		return direction;
	}

	AbstractExpression* getAction()
	{
		return action;
	}

	AbstractExpression* getDistance()
	{
		return distance;
	}
};

//方向解释器：终结符表达式
class DirectionExpression : public AbstractExpression
{
private:
	string direction;
public:
	DirectionExpression(string direction)
	{
		this->direction = direction;
	}

	//方向表达式的解释操作
	string interpret()
	{
		if (direction == "up")
		{
			return "向上";
		}
		else if (direction == "down")
		{
			return "向下";
		}
		else if (direction == "left")
		{
			return "向左";
		}
		else if (direction == "right")
		{
			return "向右";
		}
		else
		{
			return "无效指令";
		}
	}
};

//动作解释器：(终结符表达式)
class ActionExpression : public AbstractExpression
{
private:
	string action;
public:
	ActionExpression(string action)
	{
		this->action = action;
	}

	//动作移动表达式的解释操作
	string interpret()
	{
		if (action == "move")
		{
			return "移动";
		}
		else if (action == "run")
		{
			return "快速移动";
		}
		else
		{
			return "无效指令";
		}
	}
};

//距离解释器：（终结符表达式）
class DistanceExpression : public AbstractExpression
{
private:
	string distance;
public:
	DistanceExpression(string distance)
	{
		this->distance = distance;
	}

	string interpret()
	{
		return distance;
	}
};

//指令处理类：工具类
class InstructionHandler
{
private:
	AbstractExpression* mExp;

	void delTree(AbstractExpression* exp)  //删除最终的生成的抽象树
	{
		//叶子结果
		bool bLeaf = typeid(*exp) == typeid(DirectionExpression) ||
			typeid(*exp) == typeid(ActionExpression) ||
			typeid(*exp) == typeid(DistanceExpression);

		AndExpression* andExp = dynamic_cast<AndExpression*>(exp);
		SentenceExpression* sentenceExp = dynamic_cast<SentenceExpression*>(exp);

		if (bLeaf)
		{
			delete exp;
		}
		else if (andExp != NULL)  //And表达式
		{
			AbstractExpression* left = andExp->getLeft();
			AbstractExpression* right = andExp->getRight();

			delTree(left);
			delTree(right);
			delete andExp;
		}
		else if (sentenceExp != NULL) //简单句子表达式
		{
			AbstractExpression* dir = sentenceExp->getDirection();
			AbstractExpression* act = sentenceExp->getAction();
			AbstractExpression* dis = sentenceExp->getDistance();

			delTree(dir);
			delTree(act);
			delTree(dis);
			delete sentenceExp;
		}
		else
		{
		}
	}
public:
	InstructionHandler() :mExp(NULL){}

	void handle(string instruction){
		AbstractExpression* left = NULL;
		AbstractExpression* right = NULL;
		AbstractExpression* direction = NULL;
		AbstractExpression* action = NULL;
		AbstractExpression* distance = NULL;

		if (mExp != NULL)
		{
			delTree(mExp);
			mExp = NULL;
		}

		//声明一个栈对象用于存储抽象语法树
		stack<AbstractExpression*> stkExp;
		vector<string> words;
		Split(words, instruction, " "); //以空格分隔指令字符串

		for (unsigned int i = 0; i<words.size(); i++){
			//本实例采用栈的方式来处理指令，如果遇到and则将其后的三个单词连成一个简单句子（Sentence）
			//作为"and"的右表达式，而将栈顶弹出的表达式作为"and"的左表达式，最后将新的And表达式压入栈中
			string dir("");
			string act("");
			string dis("");

			if (words[i] == "and"){
				//从弹出栈顶作为and的左表达式
				left = stkExp.top();
				stkExp.pop();

				dir = words[++i];
				direction = new DirectionExpression(dir);
				act = words[++i];
				action = new ActionExpression(act);
				dis = words[++i];
				distance = new DistanceExpression(dis);

				//组成一个简单表达式作为And的右表达式
				right = new SentenceExpression(direction, action, distance);

				//生成And表达式，并压入栈中
				stkExp.push(new AndExpression(left, right));
			}
			//如果不是and表达式，就从头开始进行解释，将前3个单词作为Sentence
			//的三个操作数，生成简单表达式解析器后压入栈中
			else{
				dir = words[i];
				direction = new DirectionExpression(dir);
				act = words[++i];
				action = new ActionExpression(act);
				dis = words[++i];
				distance = new DistanceExpression(dis);

				//组成一个简单表达式作为And的右表达式
				stkExp.push(new SentenceExpression(direction, action, distance));
			}
		}

		if (!stkExp.empty()){
			mExp = stkExp.top();
			stkExp.pop();
		}
		else
			mExp = NULL;
	}

	string output(){
		return mExp == NULL ? "" : mExp->interpret();
	}

	static int test()
	{
		string instruction = "up move 5 and down run 10 and left move 5";

		InstructionHandler handler;
		handler.handle(instruction);

		cout << "输入指令: " << instruction << endl;
		cout << "移动结果：" << handler.output() << endl;

		instruction = "right run 20 and down move 10 and left run 40 and up run 10";

		handler.handle(instruction);

		cout << "输入指令: " << instruction << endl;
		cout << "移动结果：" << handler.output() << endl;

		return 0;
	}
	/*输出结果：
	输入指令: up move 5 and down run 10 and left move 5
	移动结果：向上移动5再向下快速移动10再向左移动5
	输入指令: right run 20 and down move 10 and left run 40 and up run 10
	移动结果：向右快速移动20再向下移动10再向左快速移动40再向上快速移动10
	*/
};