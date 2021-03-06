/**
 * mht
 * another honorable mention to Zahid Ghadialy
 *
 * good example to find union and intersection of two sets as arrays
 *
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
	int setOne[] = { 5, 10, 15, 20, 25 };
	int setTwo[] = { 50, 40, 30, 20, 10, 11, 21, 31, 41, 51 };

	int setOneSize = sizeof(setOne) / sizeof(int);
	int setTwoSize = sizeof(setTwo) / sizeof(int);

	//Its necessary to sort if not already sorted
	sort(setTwo, setTwo + setTwoSize);

	vector<int> unionSetVector(setOneSize + setTwoSize);
	set_union(setOne, setOne + setOneSize, setTwo, setTwo + setTwoSize, unionSetVector.begin());

	cout << "\n1. unionSetVector : ";
	copy(unionSetVector.begin(), unionSetVector.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	vector<int> intersectionSetVector(min(setOneSize, setTwoSize));
	set_intersection(setOne, setOne + setOneSize, setTwo, setTwo + setTwoSize, intersectionSetVector.begin());

	cout << "\n1. intersectionSetVector : ";
	copy(intersectionSetVector.begin(), intersectionSetVector.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << endl;
	return 0;
}