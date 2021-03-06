/**
 * mht
 *
 * hold an integer variable with its first changed value
 * 
 */
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;


class VariableHolder  
{
public:
	VariableHolder(int i = 0) :m_x_current(i), m_x_previous(i)
	{

	}

	void setValue(int i) 
	{ 
		m_x_previous = m_x_current;
		m_x_current = i;
	}
	
	VariableHolder operator = (VariableHolder const &obj)
	{
		m_x_current = obj.m_x_current;
		m_x_previous = obj.m_x_previous;
	}

	void operator = (int val)
	{
		m_x_previous = m_x_current;
		m_x_current = val;
	}

	int getCurrentX() { return m_x_current; }
	int getPreviousX() { return m_x_previous; }

private:
	int m_x_current;
	int m_x_previous;
};

int main()
{
	VariableHolder t(5); // init m_x_current and m_x_previous with 5 
	
	t = 3; // m_x_previous= 5, m_x_current= 3 
	std::cout << t.getCurrentX() << std::endl;
	std::cout << t.getPreviousX() << std::endl;
	/**
	 * 3
	 * 5
	 */


	t = 9;// m_x_previous= 3, m_x_current= 9 
	std::cout << t.getCurrentX() << std::endl;
	std::cout << t.getPreviousX() << std::endl;
	/**
	 * 9
	 * 3
	 */

	VariableHolder tt = t; // copy the same values with overloaded = operator
	std::cout << tt.getCurrentX() << std::endl;
	std::cout << tt.getPreviousX() << std::endl;
	/**
	 * 9
	 * 3
	 */

	return 0;
}