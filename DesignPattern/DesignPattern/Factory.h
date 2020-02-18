#pragma once


#include "DesignPattern.h"


// 基类
class RoleOperation
{
public:
	virtual std::string Op() = 0; // 纯虚函数
	virtual ~RoleOperation() {} // 虚析构函数
};

// 系统管理员(有 A 操作权限)
class RootAdminRole : public RoleOperation {
public:
	RootAdminRole(const std::string &roleName)
		: m_RoleName(roleName) {}
	~RootAdminRole() {
		std::cout << m_RoleName << " has been deleted!" << std::endl;
	}

	std::string Op() {
		return m_RoleName + " has A permission";
	}

private:
	std::string m_RoleName;
};


// 订单管理员(有 B 操作权限)
class OrderAdminRole : public RoleOperation {
public:
	OrderAdminRole(const std::string &roleName)
		: m_RoleName(roleName) {}
	~OrderAdminRole() {
		std::cout << m_RoleName << " has been deleted!" << std::endl;
	}

	std::string Op() {
		return m_RoleName + " has B permission";
	}

private:
	std::string m_RoleName;
};

// 普通用户(有 C 操作权限)
class NormalRole : public RoleOperation {
public:
	NormalRole(const std::string &roleName)
		: m_RoleName(roleName) {}
	~NormalRole() {
		std::cout << m_RoleName << " has been deleted!" << std::endl;
	}

	std::string Op() {
		return m_RoleName + " has C permission";
	}

private:
	std::string m_RoleName;
};

// 角色工厂
class RoleFactory {
public:
	// 获取工厂单例，工厂的实例是唯一的
	static RoleFactory& Instance() {
		static RoleFactory instance; // C++11 以上线程安全
		return instance;
	}

	// 把指针对象注册到工厂
	void RegisterRole(const std::string& name, RoleOperation* registrar) {
		m_RoleRegistry[name] = registrar;
	}

	// 根据名字name，获取对应的角色指针对象
	RoleOperation* GetRole(const std::string& name) {

		std::map<std::string, RoleOperation*>::iterator it;

		// 从map找到已经注册过的角色，并返回角色指针对象
		it = m_RoleRegistry.find(name);
		if (it != m_RoleRegistry.end()) {
			return it->second;
		}

		return nullptr; // 未注册该角色，则返回空指针
	}

private:
	// 禁止外部构造和虚构
	RoleFactory() {}
	~RoleFactory() {}

	// 禁止外部拷贝和赋值操作
	RoleFactory(const RoleFactory &);
	const RoleFactory &operator=(const RoleFactory &);

	// 保存注册过的角色，key:角色名称 , value:角色指针对象
	std::map<std::string, RoleOperation *> m_RoleRegistry;
};

//////////////////////////////////
//模板工厂（万能工厂）类
//产品注册类模板接口
//模板参数ProductType_t表示的是基类
template<class ProductType_t>
class IProductRegistrar {
public:
	//获取产品对象抽象接口
	virtual ProductType_t *CreateProduct(const std::string &name) = 0;
protected:
	//禁止外部构造和虚构，子类的"内部"的其他函数可以调用
	IProductRegistrar() {}
	virtual ~IProductRegistrar() {}
};
//工厂类模板
//模板参数ProductType_t表示的是基类
template<class ProductType_t>
class ProductFactory {
public:
	//获取工厂单例，工厂的实例是唯一的
	static ProductFactory<ProductType_t> &Instance() {
		static ProductFactory<ProductType_t> instance;
		return instance;
	}
	//产品注册
	void RegisterProduct(const std::string &name,
		IProductRegistrar<ProductType_t> *registrar) {
		m_ProductRegistry[name] = registrar;
	}
	//根据名字name，获取对应具体的产品对象
	ProductType_t *GetProduct(const std::string &name) {
		//从map找到己经注册过的产品，并返回产品对象
		if (m_ProductRegistry.find(name) != m_ProductRegistry.end()) {
			return m_ProductRegistry[name]->CreateProduct(name);
		}
		//未注册的产品，则报错未找到
		std::cout << "No product found for " << name << std::endl;
		return NULL;
	}
private:
	//禁止外部构造和虚构
	ProductFactory() {}
	~ProductFactory() {}
	//禁止外部拷贝和赋值操作
	ProductFactory(const ProductFactory &);
	const ProductFactory &operator=(const ProductFactory &);
	//保存注册过的产品
	std::map<std::string, IProductRegistrar<ProductType_t> *> m_ProductRegistry;
};
//产品注册类模板
//模板参数ProductType_t表示的是基类，ProductImpl_t表示的是派生类
template<class ProductType_t, class ProductImpl_t>
class ProductRegistrar : public IProductRegistrar<ProductType_t> {
public:
	//构造函数，只能显示调用
	explicit ProductRegistrar(const std::string & name) {
		//注册产品到工厂
		ProductFactory<ProductType_t>::Instance().RegisterProduct(name, this);
	}
	//创建指向派生类对象的指针
	ProductType_t *CreateProduct(const std::string & name) {
		return new ProductImpl_t(name);
	}
};
//////////////////////////////////

void factoryTest();
void factoryTestFactory();
void factoryTestFactorySharedPtr();