/**
 * mht
 *
 */
#include <iostream>
#include <typeinfo>

using namespace std;

// let's create a custom type
typedef std::make_unsigned<volatile long>::type long_type;

// some dummy function which returns auto but says I'm gonna return int
auto t1()->int
{
	return 100;
}

// still dummy but fancier
template<class T >
auto t2(T a)->decltype(a)
{
	return a;
}

int main()
{
	auto int_a = 6;
	auto str_a = "mokoko";
	auto dbl_a = 6.7;
	auto flt_a = 3.4f;
	auto ldl_a = 3.6L;
	auto sci_a = 3.4e+10; // this should be double
	auto bol_a = true;
	decltype(dbl_a) dbl_b = 9;

	long_type x = 999;
	auto xx = x;

	cout << int_a << " as: " << typeid(int_a).name() << endl;
	cout << str_a << " as: " << typeid(str_a).name() << endl;
	cout << dbl_a << " as: " << typeid(dbl_a).name() << endl;
	cout << flt_a << " as: " << typeid(flt_a).name() << endl;
	cout << ldl_a << " as: " << typeid(ldl_a).name() << endl;
	cout << sci_a << " as: " << typeid(sci_a).name() << endl;
	cout << bol_a << " as: " << typeid(bol_a).name() << endl;
	cout << dbl_b << " as: " << typeid(dbl_b).name() << endl;
	cout << xx	  << " as: " << typeid(xx).name() << endl;

	cout << endl;
	
	cout << t1()  << " as: " << typeid(t1()).name()  << " from " << typeid(t1).name() << endl;
	cout << t2(str_a)  << " as: " << typeid(t2(str_a)).name() << " from " << typeid(t2(str_a)).name() << endl;



	return 0;
}