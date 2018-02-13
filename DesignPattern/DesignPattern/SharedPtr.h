//shared_ptr.h
//

#pragma once

#include "DesignPattern.h"

template<class T>
class shared_ptr {
private:
	class implement {
	public:
		implement(T * pp) : p(pp), refs(1) {

		}
		~implement() {
			delete p;
			printf("p has been deleted\n");
		}

		T* p;
		size_t refs;
	};
	implement* _impl;
public:
	explicit shared_ptr(T *p) :
		_impl(new implement(p)){

	}

	~shared_ptr() {
		decrease();
	}

	shared_ptr(const shared_ptr& rhs) :
		_impl(rhs._impl) {
		increase();
	}

	shared_ptr& operator=(const shared_ptr& rhs) {
		if (_impl != rhs._impl) {//avoid self 
			decrease();
			_impl = rhs._impl;
			increase();
		}
		return *this;
	}

	T* operator->() const {
		return _impl->p;
	}
	T& operator*() const {
		return *(_impl->p);
	}

private:
	void decrease(){
		if (--(_impl->refs) == 0) {
			delete _impl;
		}
	}

	void increase() {
		++(_impl->refs);
	}
};

