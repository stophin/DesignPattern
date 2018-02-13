
#include "DesignPattern.h"

//使用private构造和析构函数
//禁止创建栈对象
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