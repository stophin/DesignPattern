
#include "Factory.h"


void InitializeRole() // 初始化角色到工厂
{
	static bool bInitialized = false;

	if (bInitialized == false) {
		// 注册系统管理员
		RoleFactory::Instance().RegisterRole("ROLE_ROOT_ADMIN", new RootAdminRole("ROLE_ROOT_ADMIN"));
		// 注册订单管理员
		RoleFactory::Instance().RegisterRole("ROLE_ORDER_ADMIN", new OrderAdminRole("ROLE_ORDER_ADMIN"));
		// 注册普通用户
		RoleFactory::Instance().RegisterRole("ROLE_NORMAL", new NormalRole("ROLE_NORMAL"));
		bInitialized = true;
	}
}
class JudgeRole {
public:
	std::string Judge(const std::string &roleName) {
		return RoleFactory::Instance().GetRole(roleName)->Op();
	}
};
void factoryTest() {
	InitializeRole(); // 优先初始化所有角色到工厂

	JudgeRole judgeRole;

	std::cout << judgeRole.Judge("ROLE_ROOT_ADMIN") << std::endl;
	std::cout << judgeRole.Judge("ROLE_ORDER_ADMIN") << std::endl;
	std::cout << judgeRole.Judge("ROLE_NORMAL") << std::endl;
}

//////////////////////////////////
void InitializeRoleFactory() // 初始化角色到工厂
{
	static bool bInitializedFactory = false;

	if (bInitializedFactory == false) {
		// 注册系统管理员
		static ProductRegistrar<RoleOperation, RootAdminRole> rootRegistrar("ROLE_ROOT_ADMIN");
		// 注册订单管理员
		static ProductRegistrar<RoleOperation, OrderAdminRole> orderRegistrar("ROLE_ORDER_ADMIN");
		// 注册普通用户
		static ProductRegistrar<RoleOperation, NormalRole> normalRegistrar("ROLE_NORMAL");
		bInitializedFactory = true;
	}
}
class JudgeRoleFactory {
public:
	std::string Judge(const std::string &roleName) {
		ProductFactory<RoleOperation>& factory = ProductFactory<RoleOperation>::Instance();
		// 从工厂获取对应的指针对象
		RoleOperation *pRoleOperation = factory.GetProduct(roleName);
		// 调用角色的对应操作权限
		std::string result = pRoleOperation->Op();
		// 手动释放资源
		delete pRoleOperation;
		return result;
	}
}; 
void factoryTestFactory() {
	InitializeRoleFactory(); // 优先初始化所有角色到工厂

	JudgeRoleFactory judgeRole;

	std::cout << judgeRole.Judge("ROLE_ROOT_ADMIN") << std::endl;
	std::cout << judgeRole.Judge("ROLE_ORDER_ADMIN") << std::endl;
	std::cout << judgeRole.Judge("ROLE_NORMAL") << std::endl;
}
class JudgeRoleFactorySharedPtr {
public:
	std::string Judge(const std::string &roleName) {
		ProductFactory<RoleOperation>& factory = ProductFactory<RoleOperation>::Instance();
		std::shared_ptr<RoleOperation> pRoleOperation(factory.GetProduct(roleName));
		return pRoleOperation->Op();
	}
};
void factoryTestFactorySharedPtr() {
	InitializeRoleFactory(); // 优先初始化所有角色到工厂

	JudgeRoleFactorySharedPtr judgeRole;

	std::cout << judgeRole.Judge("ROLE_ROOT_ADMIN") << std::endl;
	std::cout << judgeRole.Judge("ROLE_ORDER_ADMIN") << std::endl;
	std::cout << judgeRole.Judge("ROLE_NORMAL") << std::endl;
}
//////////////////////////////////