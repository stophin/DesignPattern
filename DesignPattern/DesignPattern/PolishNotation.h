
#ifndef _POLISH_NOTATION_H_
#define _POLISH_NOTATION_H_

#include "DesignPattern.h"

/*
*  函数功能：将中缀表达式转换为后缀表达式
*  参数： expression: 待转换的中缀表达式
*  返回值： 已经转换好的后缀表达式
*/
char * toReversePolishNotation(const char * expression, char * result);
/*
*  函数功能： 将中缀表达式转换为前缀表达式
*  参数： expression: 待转换的中缀表达式
*  返回值： 已经转换好的前缀表达式
*/
char * toPolishNotation(const char * expression, char * result);

#endif