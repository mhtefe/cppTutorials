/**
 * mht
 *
 * There're quite number of high level programming languages supports dynamic function parameters, i mean without strict definition of function parameters
 * 
 * c++ gives chances by using variadic templates.
 * 
 * stackoverflow is great as always
 *
 * https://stackoverflow.com/questions/1657883/variable-number-of-arguments-in-c
 */

#include <iostream>
#include <string>
#include <initializer_list>

template <typename T>
void func(T t)
{
	std::cout <<"final: " << t << std::endl;
}

template<typename T, typename... Args>
void func(T t, Args... args) // recursive variadic function
{
	std::cout << "size of params of : " << sizeof...(args) << std::endl;
	std::cout << t << std::endl;

	func(args...);
}

template <class T>
void func2(std::initializer_list<T> list)
{
	for (auto elem : list)
	{
		std::cout << elem << std::endl;
	}
}

int main()
{
	std::string
		str1("Hello"),
		str2("world");

	func(1, str1, str2, 'a', 'b');

	func2({ 10, 20, 30, 40 });

	func2({ str1, str2 });

	return 0;
}