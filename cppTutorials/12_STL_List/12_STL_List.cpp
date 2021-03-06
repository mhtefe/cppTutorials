/**
 * mht
 *
 * tutorial from programming cave (John Purcell)
 */
#include <iostream>
#include <list>

using namespace std;

int main()
{
	list<double> myList;

	myList.push_back(0);
	myList.push_back(1);
	myList.push_back(2);
	myList.push_front(-1);

	list<double>::iterator it = myList.begin();
	myList.insert(it, -2);
	it++;
	myList.insert(it, -0.5);

	it = myList.begin();
	while (it != myList.end())
	{
		if (*it == 0) // push -0.1 in front of zero
		{
			myList.insert(it, -0.1);
		}

		if (*it == 1) // erase value 1
		{
			it = myList.erase(it); // dont forget to assign iterator in order to keep it valid
		}
		else
		{
			it++; // for while loop
		}
	}

	// cout the values
	for (list<double>::iterator it = myList.begin(); it != myList.end(); ++it )
	{
		cout << *it << endl;
	}

	return 0;
}