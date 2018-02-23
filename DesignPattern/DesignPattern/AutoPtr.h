//AutoPtr.h
//

#ifndef _AUTO_PTR_H_
#define _AUTO_PTR_H_

namespace Auto_Ptr {
#define DEBUG_DECONSTRUCTOR

	template<class T>
	class auto_ptr {
	public:
		T * m_ptr;//被封装的指针
	public:
		//默认构造函数
		auto_ptr() :m_ptr(NULL) {

		}
		//构造函数
		auto_ptr(T *p) :m_ptr(p) {
		}
		//复制构造函数
		auto_ptr(auto_ptr& mp) {
			m_ptr = mp.getPtr();//mp原来的指针失效
		}
		T* getPtr() {
			T* tmp = m_ptr;
			m_ptr = NULL;//失效
			return tmp;
		}
		//析构函数
		~auto_ptr() {
			if (m_ptr) {
				delete m_ptr;
#ifdef DEBUG_DECONSTRUCTOR
				printf("ptr deleted\n");
#endif
			}
		}

		T& operator*() {
			return *m_ptr;
		}
		T* operator->() {
			return m_ptr;
		}
		//造型复制操作符
		auto_ptr& operator=(auto_ptr& ap) {
			if (&ap != this) {
				if (m_ptr) {
					delete m_ptr;
#ifdef DEBUG_DECONSTRUCTOR
					printf("ptr deleted\n");
#endif
				}
				m_ptr = ap.getPtr();
			}
			return *this;
		}
	};

	void test() {
		auto_ptr<int> mInt(new int(8));

		printf("%d\n", *mInt);

		struct test_s {
			int a;
			int b;
			float c;
		};

		auto_ptr<test_s> mS(new test_s());
		mS->a = 10;
		mS->b = 20;
		mS->c = 0.123;

		printf("%d\t%d\t%f\n", mS->a, mS->b, mS->c);

		//注意下面的所有权转移
		//注意这一步以后mS不能用了
		auto_ptr<test_s> _mS(mS);
		printf("%d\t%d\t%f\n", _mS->a, _mS->b, _mS->c);

		//注意这一步以后_mS不能用了
		auto_ptr<test_s> __mS;
		__mS = _mS;
		printf("%d\t%d\t%f\n", __mS->a, __mS->b, __mS->c);

	}
}

#endif