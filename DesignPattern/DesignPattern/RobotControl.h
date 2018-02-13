//��Ϊ��ģʽ��������ģʽ
//����������һ�׻����˿��Ƴ���
/*˵����
�����˿��Ƴ����а���һЩ�򵥵�Ӣ�Ŀ���ָ�ÿһ��ָ���Ӧһ�����ʽ(expression)��
�ñ��ʽ�����Ǽ򵥱��ʽҲ�����Ǹ��ϱ��ʽ��ÿһ���򵥱��ʽ���ƶ�����(direction)��
�ƶ���ʽ(action)���ƶ�����(distance)��������ɣ������ƶ����������(up)����(down)��
��(left)����(right)���ƶ���ʽ�����ƶ�(move)�Ϳ����ƶ�(run)���ƶ�����Ϊһ����������
�������ʽ֮�����ͨ����(and)���ӣ��γɸ���(composite)���ʽ��
�û�ͨ����ͼ�λ������ý�����в������Դ���һ�������˿���ָ����������յ�ָ��
�󽫰���ָ������ý����ƶ��������������ָ�up move 5���������ƶ�5����λ���������
��ָ�down  run 10 and left move 20�������¿����ƶ�10����λ�������ƶ�20����λ����
*/

/*�ķ�����
expression ::= direction action distance | composite //���ʽ
composite ::= expression 'and' expression //���ϱ��ʽ
direction ::= 'up' | 'down' | 'left' | 'right' //�ƶ�����
action ::= 'move' | 'run' //�ƶ���ʽ
distance ::= an integer //�ƶ�����
��������һ�������������ķ����򣬶�Ӧ������Ե�λ����Щ���Ե�λ���Է�Ϊ���࣬
�ս����Ҳ��Ϊ�ս�����ʽ��������direction��action��distance�����������Ե���С��ɵ�λ�������ٽ��в�֣�
���ս����Ҳ��Ϊ���ս�����ʽ��������expression��composite�����Ƕ���һ�������ľ��ӣ�����һϵ���ս������ս����
*/

//��ʵ���Ի����˿���ָ�������������ģ�⣬��Ӣ��ָ���Ϊ����ָ�ʵ������ǵ��ò�ͬ�Ŀ��Ƴ�����л����˵Ŀ��ƣ�
//�������ƶ����򡢷�ʽ�;���Ŀ��Ƶ�
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <typeinfo>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// �ַ����ָ�
//
// -------------------------------------------------------------------------
// ����     : Split
// ����     : �ָ�STL��׼�ַ���
// ����ֵ   : void
// ����     : Container<std::basic_string<CharT> >& v ��ŷָ���
// ����     : const std::basic_string<CharT>& s ���ָ��ַ���
// ����     : const std::basic_string<CharT>& c �ָ��ַ���
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

//�����ࣺ������
class AbstractExpression
{
public:
	virtual string interpret() = 0;
	virtual ~AbstractExpression(){}
};
//And�����������ս�����ʽ
class AndExpression : public AbstractExpression
{
private:
	AbstractExpression* left; //And������ʽ
	AbstractExpression* right; //And���ұ��ʽ
public:
	AndExpression(AbstractExpression* left,
		AbstractExpression* right)
	{
		this->left = left;
		this->right = right;
	}

	//And���ʽ���Ͳ���
	string interpret()
	{
		return left->interpret() + "��" + right->interpret();
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

//�򵥾��ӽ����������ս�����ʽ
//�磺up move 5����ʾ�������ƶ�5����λ
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

	//���Ͳ���
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

//������������ս�����ʽ
class DirectionExpression : public AbstractExpression
{
private:
	string direction;
public:
	DirectionExpression(string direction)
	{
		this->direction = direction;
	}

	//������ʽ�Ľ��Ͳ���
	string interpret()
	{
		if (direction == "up")
		{
			return "����";
		}
		else if (direction == "down")
		{
			return "����";
		}
		else if (direction == "left")
		{
			return "����";
		}
		else if (direction == "right")
		{
			return "����";
		}
		else
		{
			return "��Чָ��";
		}
	}
};

//������������(�ս�����ʽ)
class ActionExpression : public AbstractExpression
{
private:
	string action;
public:
	ActionExpression(string action)
	{
		this->action = action;
	}

	//�����ƶ����ʽ�Ľ��Ͳ���
	string interpret()
	{
		if (action == "move")
		{
			return "�ƶ�";
		}
		else if (action == "run")
		{
			return "�����ƶ�";
		}
		else
		{
			return "��Чָ��";
		}
	}
};

//��������������ս�����ʽ��
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

//ָ����ࣺ������
class InstructionHandler
{
private:
	AbstractExpression* mExp;

	void delTree(AbstractExpression* exp)  //ɾ�����յ����ɵĳ�����
	{
		//Ҷ�ӽ��
		bool bLeaf = typeid(*exp) == typeid(DirectionExpression) ||
			typeid(*exp) == typeid(ActionExpression) ||
			typeid(*exp) == typeid(DistanceExpression);

		AndExpression* andExp = dynamic_cast<AndExpression*>(exp);
		SentenceExpression* sentenceExp = dynamic_cast<SentenceExpression*>(exp);

		if (bLeaf)
		{
			delete exp;
		}
		else if (andExp != NULL)  //And���ʽ
		{
			AbstractExpression* left = andExp->getLeft();
			AbstractExpression* right = andExp->getRight();

			delTree(left);
			delTree(right);
			delete andExp;
		}
		else if (sentenceExp != NULL) //�򵥾��ӱ��ʽ
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

		//����һ��ջ�������ڴ洢�����﷨��
		stack<AbstractExpression*> stkExp;
		vector<string> words;
		Split(words, instruction, " "); //�Կո�ָ�ָ���ַ���

		for (unsigned int i = 0; i<words.size(); i++){
			//��ʵ������ջ�ķ�ʽ������ָ��������and������������������һ���򵥾��ӣ�Sentence��
			//��Ϊ"and"���ұ��ʽ������ջ�������ı��ʽ��Ϊ"and"������ʽ������µ�And���ʽѹ��ջ��
			string dir("");
			string act("");
			string dis("");

			if (words[i] == "and"){
				//�ӵ���ջ����Ϊand������ʽ
				left = stkExp.top();
				stkExp.pop();

				dir = words[++i];
				direction = new DirectionExpression(dir);
				act = words[++i];
				action = new ActionExpression(act);
				dis = words[++i];
				distance = new DistanceExpression(dis);

				//���һ���򵥱��ʽ��ΪAnd���ұ��ʽ
				right = new SentenceExpression(direction, action, distance);

				//����And���ʽ����ѹ��ջ��
				stkExp.push(new AndExpression(left, right));
			}
			//�������and���ʽ���ʹ�ͷ��ʼ���н��ͣ���ǰ3��������ΪSentence
			//�����������������ɼ򵥱��ʽ��������ѹ��ջ��
			else{
				dir = words[i];
				direction = new DirectionExpression(dir);
				act = words[++i];
				action = new ActionExpression(act);
				dis = words[++i];
				distance = new DistanceExpression(dis);

				//���һ���򵥱��ʽ��ΪAnd���ұ��ʽ
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

		cout << "����ָ��: " << instruction << endl;
		cout << "�ƶ������" << handler.output() << endl;

		instruction = "right run 20 and down move 10 and left run 40 and up run 10";

		handler.handle(instruction);

		cout << "����ָ��: " << instruction << endl;
		cout << "�ƶ������" << handler.output() << endl;

		return 0;
	}
	/*��������
	����ָ��: up move 5 and down run 10 and left move 5
	�ƶ�����������ƶ�5�����¿����ƶ�10�������ƶ�5
	����ָ��: right run 20 and down move 10 and left run 40 and up run 10
	�ƶ���������ҿ����ƶ�20�������ƶ�10����������ƶ�40�����Ͽ����ƶ�10
	*/
};