#include <memory>
#include <iostream>
#include <cstdlib>

// unique_ptr
// shared_ptr
// weak_ptr

// auto_ptr

struct B;

struct A
{
	std::shared_ptr<B> b_link;
	~A() { std::cout << "A::~A()" << std::endl; }
};

struct B
{
	std::shared_ptr<A> a_link;
	~B() { std::cout << "B::~B()" << std::endl; }
};

int main()
{
	std::shared_ptr<A> a = std::make_shared<A>();
	std::shared_ptr<B> b = std::make_shared<B>();

	a->b_link = b;
	b->a_link = a;

	system("pause");
	return 0; 
}