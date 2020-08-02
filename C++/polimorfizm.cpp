#include <iostream>
#include <memory>
#include<vector>

class Base {
	public:
	virtual void SayHello() const = 0; //pure virtual function, isn't used
	/*{
	std::cout << "Hello from Base!" << std::endl;
	}*/
};

class Derived : public Base {
	public:
	void SayHello() const override {
	std::cout << "Hello from Derived!" << std::endl;
	}
};

class DerivedDerived : public Base {
	public:
	void SayHello() const override {
	std::cout << "Hello from DerivedDerived!" << std::endl;
	}
};

int main() {
	Base *pBase = new Derived();
	Base *pBase2 = new DerivedDerived();
	//Base *pBase3 = new Base();
	
	//pBase->SayHello();
	//pBase2->SayHello();
	
	std::vector<Base*> v_modules;
	v_modules.push_back(pBase);
	v_modules.push_back(pBase2);
	//v_modules.push_back(pBase3);
	
	for(auto m : v_modules) {
	m->SayHello();
	}
}
