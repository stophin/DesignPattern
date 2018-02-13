

#include "PolishNotation.h"


string analyData(const char * str, int &i) {
	int temp = i++;
	while (str[i] && str[i] >= 0 && str[i] <= '9') {
		i++;
	}
	string s(str + temp, str + i);
	return s;
}
string analyStr(const char * str, int &i) {
	int temp = i++;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') ||
		(str[i] >= 'A' && str[i] <= 'Z'))) {
		i++;
	}
	string s(str + temp, str + i);
	return s;
}

void toPolishNotation(const char * str, char * post_str) {
	//存放运算符表达式的栈
	stack<char> oper_stk;
	vector<string> post_vec;
	string data;

	//将中缀表达式转换为后缀表达式
	int i;
	for (i = 0; str[i]; i++) {
		//如果该字符为数字或字符，解析并压入栈
		if (str[i] >= '0' && str[i] <= '9') {
			data = analyData(str, i);
			post_vec.push_back(data);
			i--;
		}
		else if ((str[i] >= 'a' && str[i] <= 'z') ||
			(str[i] >= 'A' && str[i] <= 'Z')) {
			data = analyStr(str, i);
			post_vec.push_back(data);
			i--;
		}
		else if (str[i] == '(') {
			oper_stk.push(str[i]);
		}
		else if (str[i] == ')') {
			char ch_temp[2] = { 0 };
			ch_temp[0] = oper_stk.top();
			while (ch_temp[0] != '(') {
				string str_temp(ch_temp);
				post_vec.push_back(str_temp);
				oper_stk.pop();

				ch_temp[0] = oper_stk.top();
			}
			oper_stk.pop();
		}
		else if (str[i] == '+' || str[i] == '-') {
			char ch_temp[2] = { 0 };
			//全部出栈，直到碰到"("
			while (oper_stk.size() != 0) {
				ch_temp[0] = oper_stk.top();
				if (ch_temp[0] == '(') {
					break;
				}
				oper_stk.pop();

				string str_temp(ch_temp);
				post_vec.push_back(str_temp);
			}
			//当前表达式符号入栈
			oper_stk.push(str[i]);
		}
		else if (str[i] == '*' || str[i] == '/') {
			char ch_temp[2] = { 0 };
			//全部出栈，直到碰到"(""+""-"
			while (oper_stk.size() != 0) {
				ch_temp[0] = oper_stk.top();
				if (ch_temp[0] == '(' ||
					ch_temp[0] == '+' ||
					ch_temp[0] == '-') {
					break;
				}
				oper_stk.pop();

				string str_temp(ch_temp);
				post_vec.push_back(str_temp);
			}
			//当前表达式符号入栈
			oper_stk.push(str[i]);
		}
	}

	while (!oper_stk.empty()) {
		char ch_temp[2] = { 0 };
		ch_temp[0] = oper_stk.top();
		oper_stk.pop();

		string str_temp(ch_temp);
		post_vec.push_back(str_temp);
	}

	for (vector<string>::iterator it = post_vec.begin(); it != post_vec.end(); it++){
		printf("%s", it->c_str());
	}
}