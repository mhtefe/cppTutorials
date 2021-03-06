/**
 * mht
 *
 * "const" can be confusing sometimes, and I wanted to sum it up its usage including const_cast
 *
 * Definition				Read-only		Ownership passed		Allows NULL
 *
 *  Type&						No				No						No
 *
 *  const Type&					Yes				No						No
 *
 *	Type*						No				Yes						Yes
 *
 *	const Type*					Yes				Yes						Yes
 *	
 *  Type* const					No				No						Yes
 *
 *	const Type* const			Yes				No						Yes
 * 
 *
 * From Zahid Ghadialy:
 *		It may be sometimes confusing to remember is the const is associated with the pointer or the variable. 
		A simpler way to remember is that const is applied to whatever it is near. 
		Another thing is that You have to read pointer declarations right-to-left. So:

		const X* p means “p points to an X that is const”: the X object can’t be changed via p.

		X* const p means “p is a const pointer to an X that is non-const”: you can’t change the pointer p itself, but you can change the X object via p.

		const X* const p means “p is a const pointer to an X that is const”: you can’t change the pointer p itself, nor can you change the X object via p.

		https://isocpp.org/wiki/faq/const-correctness#overview-const

 */
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	/**
	 * 1
	 */
	const int c1 = 98; // c1 is read only
	//c1 = 0; // can't assign to const variable



	/**
	 * 2
	 */
	const int * c2; //c2 is a variable pointer to a constant integer. No initialization required, can be used for assignment
					//int const * c2; is the same

	const int value0 = 22;
	c2 = &value0;
	//*c2 = 33; // not valid
	int value1 = 33;
	c2 = &value1; // this works fine
	value1 = 44; // so c2 is 44



	/**
	 * 3
	 */
	int value2 = 0;
	int value3 = 1;
	int * const c3 = &value2; //c3 is constant pointer to a variable integer
	//int * const c3; // won't compile, initializaion required
	//c3 = &value3; // also wont work, different from usage above
	value2 = 333; // valid way to change value of c3

	/**
	 * 4
	 */
	int value5 = 55;
	int const * const c4 = &value5; // c4 is constant pointer to a constant integer; total lock for changing pointer address or its value through the pointer. 


	/**
	 * 5
	 */
	// there's something like const_cast
	int i = 0;
	const int& ref = i;
	const int* ptr = &i;

	// we can change the value of "i" by following:
	const_cast<int&>(ref) = 33;
	*const_cast<int*>(ptr) = 44;
	//ref = 33; // cannot assign const var.


	/**
	 * sounds good but doesn't work
	 */ 
	const int ii = 0;
	const int& reff = ii;
	const int* ptrr = &ii;

	const_cast<int&>(reff) = 66;
	*const_cast<int*>(ptrr) = 99;

	cout <<"ii: " << ii << endl;
	cout <<"reff: " << reff << endl;
	cout <<"*ptrr: " << *ptrr << endl;
	
	// therefore, we use volatile 
	const volatile int iii = 0;
	const volatile int* ptrrr = &iii;
	*const_cast<int*>(ptrrr) = 99;
	cout << "iii: " << iii << endl;
	
	return 0;
}