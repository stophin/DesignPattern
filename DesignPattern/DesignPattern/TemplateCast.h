//TemplateCast.h
//

#ifndef _TEMPLATE_CAST_H_
#define _TEMPLATE_CAST_H_

//模板隐式类型转换
namespace Template_Cast {

	template <typename T>
	class A
	{
	public:
		A(T _a) :m_a(_a){}
		void print()
		{
			cout << m_a << endl;
		}
		T m_a;


		//这里加一个他类型转化
		template<typename U>
		A(A<U>& _a) :m_a(_a.m_a){}
	};


	int test()
	{
		A<int> aint(20);
		A<float> afloat(50);

		aint.print();
		afloat.print();

		afloat = aint;

		aint.print();
		afloat.print();

		return 0;
	}
}

//怪异的循环模板模式
//这个不太清楚，不用了解
namespace Template_Loop {
	class NewHandlerHolder
	{
	public:
		explicit NewHandlerHolder(new_handler nh)
			: handler(nh) {}
		~NewHandlerHolder()
		{
			set_new_handler(handler);
		}
	private:
		new_handler handler;
	};

	template<typename T>
	class NewHandlerSurpport
	{
	public:
		static new_handler set_new_handler(new_handler) throw();
		static void* operator new (size_t size) throw(bad_alloc);
	private:
		static new_handler currentHandler;
	};

	template<typename T>
	new_handler NewHandlerSurpport<T>::set_new_handler(new_handler p) throw()
	{
		new_handler oldHander = currentHandler;
		currentHandler = p;
		return oldHander;
	}

	template<typename T>
	void* NewHandlerSurpport<T>::operator new (size_t size) throw(bad_alloc)
	{
		NewHandlerHolder h(std::set_new_handler(currentHandler));
		return ::operator new(size);
	}

	template<typename T>
	new_handler NewHandlerSurpport<T>::currentHandler = 0;

	class Test : public NewHandlerSurpport<Test>
	{
	public:
		int val;
	};

	void test() {
		Test test;
		test.val = 1023;
		printf("%d\n", test.val);

		Test * ptest = new Test;
		ptest->val = 1024;
		printf("%d\n", ptest->val);

	}
}

#endif