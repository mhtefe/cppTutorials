/**
 * mht
 *
 */
#include <iostream>
#include <vector>

using namespace std;


class ABC
{
public:
	int f1(int a, int b)
	{
		x = a, y = b;
		cout << "x = " << x << " and y = " << y << endl;
		return 0;
	}
	int f2(int a, int b) const
	{
		//x = a; - COMPILE ERROR because its const
		int *temp = const_cast<int*>(&x); //Removing the const
		*temp = a; //OK now
		y = b; //OK because its defined as mutable
		cout << "x = " << x << " and y = " << y << endl;
		return 0;
	}

	int f3(const int &a,  int const &b)
	{
		// a++; Compile error, a is constant function member
		x = a;
		y = b;
	}

private:
	int x;
	mutable int y;
};


int main()
{
	ABC abc;
	abc.f1(3, 7);
	abc.f2(20, 40);
	abc.f3(1, 2);

	return 0;
}