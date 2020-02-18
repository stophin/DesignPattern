
#include "Factory.h"


void InitializeRole() // ��ʼ����ɫ������
{
	static bool bInitialized = false;

	if (bInitialized == false) {
		// ע��ϵͳ����Ա
		RoleFactory::Instance().RegisterRole("ROLE_ROOT_ADMIN", new RootAdminRole("ROLE_ROOT_ADMIN"));
		// ע�ᶩ������Ա
		RoleFactory::Instance().RegisterRole("ROLE_ORDER_ADMIN", new OrderAdminRole("ROLE_ORDER_ADMIN"));
		// ע����ͨ�û�
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
	std::cout << "factoryTest" << std::endl;

	InitializeRole(); // ���ȳ�ʼ�����н�ɫ������

	JudgeRole judgeRole;

	std::cout << judgeRole.Judge("ROLE_ROOT_ADMIN") << std::endl;
	std::cout << judgeRole.Judge("ROLE_ORDER_ADMIN") << std::endl;
	std::cout << judgeRole.Judge("ROLE_NORMAL") << std::endl;
}

//////////////////////////////////
//���ܹ�������
void InitializeRoleFactory() // ��ʼ����ɫ������
{
	static bool bInitializedFactory = false;

	if (bInitializedFactory == false) {
		// ע��ϵͳ����Ա
		static ProductRegistrar<RoleOperation, RootAdminRole> rootRegistrar("ROLE_ROOT_ADMIN");
		// ע�ᶩ������Ա
		static ProductRegistrar<RoleOperation, OrderAdminRole> orderRegistrar("ROLE_ORDER_ADMIN");
		// ע����ͨ�û�
		static ProductRegistrar<RoleOperation, NormalRole> normalRegistrar("ROLE_NORMAL");
		bInitializedFactory = true;
	}
}
class JudgeRoleFactory {
public:
	std::string Judge(const std::string &roleName) {
		ProductFactory<RoleOperation>& factory = ProductFactory<RoleOperation>::Instance();
		// �ӹ�����ȡ��Ӧ��ָ�����
		RoleOperation *pRoleOperation = factory.GetProduct(roleName);
		// ���ý�ɫ�Ķ�Ӧ����Ȩ��
		std::string result = pRoleOperation->Op();
		// �ֶ��ͷ���Դ
		delete pRoleOperation;
		return result;
	}
}; 
void factoryTestFactory() {
	std::cout << "factoryTestFactory" << std::endl;

	InitializeRoleFactory(); // ���ȳ�ʼ�����н�ɫ������

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
	std::cout << "factoryTestFactorySharedPtr" << std::endl;

	InitializeRoleFactory(); // ���ȳ�ʼ�����н�ɫ������

	JudgeRoleFactorySharedPtr judgeRole;

	std::cout << judgeRole.Judge("ROLE_ROOT_ADMIN") << std::endl;
	std::cout << judgeRole.Judge("ROLE_ORDER_ADMIN") << std::endl;
	std::cout << judgeRole.Judge("ROLE_NORMAL") << std::endl;
}
//////////////////////////////////


//////////////////////////////////
//����ģʽ����
//////////////////////////////////
class JudgeRoleContext {
public:
	std::string Judge(RoleOperation *pOperation) {
		RoleContext roleContext(pOperation);
		return roleContext.execute();
	}
};
void facotryTestContext() {
	std::cout << "facotryTestContext" << std::endl;

	JudgeRoleContext judgeRole;

	std::cout << judgeRole.Judge(new RootAdminRole("ROLE_ROOT_ADMIN")) << std::endl;
	std::cout << judgeRole.Judge(new OrderAdminRole("ROLE_ORDER_ADMIN")) << std::endl;
	std::cout << judgeRole.Judge(new NormalRole("ROLE_NORMAL")) << std::endl;
}
//////////////////////////////////

//////////////////////////////////
//���ܲ���ģʽ����
class JudgeRoleContextTemplate {
public:
	std::string Judge(RoleOperation *pOperation) {
		ProductContextTemplate<RoleOperation> roleContext(pOperation);
		return roleContext.execute();
	}
};
void factoryTestContextTemplate() {
	std::cout << "factoryTestContextTemplate" << std::endl;

	JudgeRoleContextTemplate judgeRole;

	std::cout << judgeRole.Judge(new RootAdminRole("ROLE_ROOT_ADMIN")) << std::endl;
	std::cout << judgeRole.Judge(new OrderAdminRole("ROLE_ORDER_ADMIN")) << std::endl;
	std::cout << judgeRole.Judge(new NormalRole("ROLE_NORMAL")) << std::endl;
}
//////////////////////////////////