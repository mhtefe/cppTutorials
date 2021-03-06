/**
 * mht
 *
 * tutorial from programming cave (John Purcell)
 */
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<double> nums(20, 3); // 20 elements with 3 as initial value

	cout << nums.size() << endl; // obviously 20

	nums.push_back(0);
	nums.push_back(1);

	cout << nums.size() << endl; // stack new pushes after size 20

	int cap = nums.capacity(); // capacity is bigger than beginnig
	cout <<"initial cap: " << cap << endl;

	for (int i = 0; i< 10000; ++i)
	{
		if (nums.capacity() != cap)
		{
			cap = nums.capacity();
			cout << "cap in loop: " << cap << endl;
		}

		nums.push_back(i);
	}

	nums.clear();
	cout << "after clear cap: " << nums.capacity() << endl; // capacity remains the same
	cout << "after clear size: " << nums.size() << endl; // clears all elements and set size 0

	nums.resize(20);
	cout << "last cap: " << nums.capacity() << endl; // capacity remains same
	cout << "last size: " << nums.size() << endl; // size increases to 20

	nums.reserve(100000);
	cout << "last cap: " << nums.capacity() << endl; // capacity increases if we feed reserve function with value bigger than previous reserve
	cout << "last size: " << nums.size() << endl; // size doesn't change

	return 0;
}