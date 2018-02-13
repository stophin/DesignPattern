
#include "DesignPattern.h"

//ʹ��private�������������
//��ֹ����ջ����
class DemoClass {
private:
	DemoClass(){
		printf("Democlass constructor\n");
	}
	~DemoClass(){
		printf("Democlass destructor\n");
	}
public:
	static DemoClass * MakeDemoClass() {
		return new DemoClass();
	}
	void Release() {
		delete this;
	}
};