/**
 * mht
 *
 * tutorial from programming cave (John Purcell)
 */
#include <iostream>
#include <map>

using namespace std;

int main()
{
	map<string, double> temps;

	temps["Norvay"] = -20;
	temps["France"] = 20;
	temps["Qatar"] = 50;

	temps.insert(make_pair("Turkey", 30));

	for (map<string, double>::iterator it = temps.begin(); it != temps.end(); it++)
	{
		cout << it->first.c_str() << " is " << it->second << " celcius degrees" << endl;
	}

	cout << temps["Germany"] << endl; // adds Germany even if it's not in the map
	for (map<string, double>::iterator it = temps.begin(); it != temps.end(); it++)
	{
		cout << it->first.c_str() << " is " << it->second << " celcius degrees" << endl;
	}

	if (temps.find("Serbia") != temps.end())
	{
		cout <<"Valid key"<< endl;
	}
	else
	{
		cout <<"Invalid key"<< endl;
	}

	return 0;
}