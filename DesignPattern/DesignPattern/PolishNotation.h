
#ifndef _POLISH_NOTATION_H_
#define _POLISH_NOTATION_H_

#include "DesignPattern.h"

/*
*  �������ܣ�����׺���ʽת��Ϊ��׺���ʽ
*  ������ expression: ��ת������׺���ʽ
*  ����ֵ�� �Ѿ�ת���õĺ�׺���ʽ
*/
char * toReversePolishNotation(const char * expression, char * result);
/*
*  �������ܣ� ����׺���ʽת��Ϊǰ׺���ʽ
*  ������ expression: ��ת������׺���ʽ
*  ����ֵ�� �Ѿ�ת���õ�ǰ׺���ʽ
*/
char * toPolishNotation(const char * expression, char * result);

#endif