//AutoPtr.h
//

#ifndef _AUTO_PTR_H_
#define _AUTO_PTR_H_

namespace Auto_Ptr {
#define DEBUG_DECONSTRUCTOR

	template<class T>
	class auto_ptr {
	public:
		T * m_ptr;//����װ��ָ��
	public:
		//Ĭ�Ϲ��캯��
		auto_ptr() :m_ptr(NULL) {

		}
		//���캯��
		auto_ptr(T *p) :m_ptr(p) {
		}
		//���ƹ��캯��
		auto_ptr(auto_ptr& mp) {
			m_ptr = mp.getPtr();//mpԭ����ָ��ʧЧ
		}
		T* getPtr() {
			T* tmp = m_ptr;
			m_ptr = NULL;//ʧЧ
			return tmp;
		}
		//��������
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
		//���͸��Ʋ�����
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

		//ע�����������Ȩת��
		//ע����һ���Ժ�mS��������
		auto_ptr<test_s> _mS(mS);
		printf("%d\t%d\t%f\n", _mS->a, _mS->b, _mS->c);

		//ע����һ���Ժ�_mS��������
		auto_ptr<test_s> __mS;
		__mS = _mS;
		printf("%d\t%d\t%f\n", __mS->a, __mS->b, __mS->c);

	}
}

#endif