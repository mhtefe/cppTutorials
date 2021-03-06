/**
 * mht
 *
 * a simple "[]" operator overloading example. & operator usage must be noticed, because if you don't use reference
 * it's not possible assign rvalue to the array inside class
 */
#include <iostream>
#include <vector>

using namespace std;

class IntList
{
private:
	int m_list[10];
public:
	// operator[]() overloading
	int& operator[] (const int index);

	int operator() (const int index);

	int& dummyFunc();
};

int& IntList::operator[] (const int index)
{
	return m_list[index];
}

int IntList::operator() (const int index)
{
	return m_list[index];
}

int& IntList::dummyFunc()
{
	int a = 4;
	return a;
}

int main()
{
	IntList list;

	list[2] = 3; // set a value

	std::cout << list[2] << endl; // get a value

	std::cout << list(2) << endl;

	// want to try sometring different to understand lvalue - rvalue thing
	list.dummyFunc() = 3; // this asssignment is valid although it's useless
	std::cout << list.dummyFunc() << endl;

	return 0;
}