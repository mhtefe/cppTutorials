/**
 * mht
 *
 * how to use function pointer and callbacks
 * 
 */
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int funcEmpty() 
{
	return 33;
}

int xAdd3(int x)
{
	return x + 3;
}

int xSub3(int x)
{
	return x - 3;
}

int callbackFcn(int(*c)(int), int x)
{
	return c(x);
}

int main()
{
	/**
	 * 1 - point to a function with void *
	 */
	void * fPtr = reinterpret_cast<void*>(funcEmpty);
	std::cout << fPtr << std::endl; // prints address of the function

	/**
	 * 2 - call function by using its pointer and std::function
	 */
	std::cout << std::endl;
	int(*fPtr2)() = funcEmpty;
	std::cout << (*fPtr2)() << std::endl; // evaluates the function
	///or
	std::function<int()> fcnPtr = funcEmpty; // more modern function pointer acts like the function itself
	std::cout << fcnPtr() << std::endl; 

	/**
	 * 3 - point function which gets parameter
	 */
	std::cout << std::endl;
	int(*fptr3)(int) = xAdd3;
	std::cout << (*fptr3)(63) << std::endl; // evaluates the function

	/**
	 * 4 - call different functions by callback
	 */
	std::cout << std::endl;
	std::cout << callbackFcn(xAdd3, 93) << std::endl;
	std::cout << callbackFcn(xSub3, 93) << std::endl;
	return 0;
}