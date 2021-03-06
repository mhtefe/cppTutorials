/**
 * mht
 *
 * I chose to brute-force calculate the summation of numbers from 1 to N as a "Hello World" example. Calculation times are measured.
 *
 * don't forget to open c++ -> language -> openmp support
 *
 * most explanations are acquired from Intel, 'A "Hands-on" introduction to OpenMP' tutorials. Quite a good reference
 */

#include <iostream>
#include <math.h>
#include <omp.h>
#include <sstream>

using namespace std;

typedef unsigned long long  uint64;

const int global_thread_num = 4;
uint64 global_total = 100000000; // give a really big number to see the effect

uint64 serialSum(uint64 _total)
{
	uint64 sum = 0;
	for (uint64 i = 1; i<= _total; i++)
	{
		sum += i;
	}
	return sum;
}

uint64 parallelPartialSum(uint64 _threadId, uint64 _totalThread, uint64 _total)
{
	uint64 f_start, f_end;
	f_start = _threadId * (_total / _totalThread) + _threadId + 1;
	if (_threadId != global_thread_num -1)
		f_end = f_start + _total / _totalThread;
	else
		f_end = _total;

	uint64 f_sum = 0;
	for (uint64 i = f_start; i<= f_end; ++i)
	{
		f_sum += i;
	}
	return f_sum;
}

int main()
{
	/*
	* test
	*/
	cout << "this machine can use " << omp_get_max_threads() << " threads. " << endl;

	// serial sum
	double st0 = omp_get_wtime();
	uint64 s_serial = serialSum(global_total);
	double et0 = omp_get_wtime();
	cout << "serial sum 1 to "<< global_total << " : " << s_serial << " in " << (et0 - st0) <<  endl;

	omp_set_num_threads(global_thread_num);
	uint64 parallel_sum = 0;
	
	double st1 = omp_get_wtime();
#pragma omp parallel				/* gives us a parallel region, everything inside runs on different threads*/
	{
		int ID = omp_get_thread_num(); 
		uint64 p_sum;
		p_sum = parallelPartialSum(ID, global_thread_num, global_total);

		// a wise man suggested to use stringstream to ensure ordered output stream (ordered strings, not thread id's)  
		stringstream s;			
		s << ID << " gives : " << p_sum << endl;
		cout << s.str();

#pragma omp atomic					/*atomic: protects only the read/update of 'parallel_sum' */
		parallel_sum += p_sum;
	}
	double et1 = omp_get_wtime();
	cout << "parallel sum 1 to " << global_total << " : " << parallel_sum << " in "<< (et1 - st1) << endl;
	return 0;
}