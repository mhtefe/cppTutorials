/**
 * mht
 *
 *  Some examples and notes on keywords of OpenMP.
 */

#include <iostream>
#include <math.h>
#include <omp.h>
#include <sstream>

using namespace std;

void test_barrier();
void test_reduction();
void test_atomic();
void test_atomic_integral_pi();
void single_master_critical();

typedef unsigned long long  uint64;

int main()
{
	//test_barrier();
	//test_reduction();
	//test_atomic();
	test_atomic_integral_pi();
	//single_master_critical();
	return 0;
}

/**
 *  barrier: Each thread waits until all threads arrive
 */
void test_barrier()
{
	printf("test_barrier\n");
	omp_set_num_threads(8);
#pragma omp parallel
	{
		printf("Hello from thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
#pragma omp barrier // all threads wait here
		printf("Thread %d of %d have passed the barrier\n", omp_get_thread_num(), omp_get_num_threads());
	}
}

/**
 * reduction: combining values into a single accumulation variable
 */
void test_reduction()
{
	printf("test_reduction\n");
	omp_set_num_threads(3);

	int maxV = 10;
	int summ = 0;
#pragma omp parallel
	{
		int i;

#pragma omp for reduction(+:summ)
		for (i = 1; i <= maxV; ++i)
		{
			printf("thread %d added %d\n", omp_get_thread_num(), i);
			summ += i;
		}
	}

	printf("sum is %d", summ);
}


/**
 * atomic: provides mutual exclusion but only applies to the update of a memory location
 */
/// this is a dummy function to use
double sum_two(int i, int j)
{
	return (i + j);  
}
void test_atomic()
{
	printf("test_atomic\n");
	omp_set_num_threads(8);

	const int nbodies = 50;
	double sum_false = 0;
	double sum_atomic = 0;
#pragma omp parallel
	{
		int i;
#pragma omp for
		for (i = 0; i< nbodies; i++)
		{
			for (int j = i + 1; j < nbodies; j++)
			{
				double eij = sum_two(i, j);
				sum_false += eij; // this is a bug, each thread will try to update sum_false without 
#pragma omp atomic
				sum_atomic += eij;
			}
		}
	}

	std::cout << "sum_atomic vs. sum_false  = " << sum_atomic << " - " << sum_false << std::endl;
}

/**
 * parallel solution to calculation of pi using integral equation on tutorials page
 */
void test_atomic_integral_pi()
{
	uint64 numSteps = 10000000000;
	double step = 1.0 / (double)numSteps;
	double pi_val = 0.0;

	omp_set_num_threads(8);
	double s_time = omp_get_wtime();
#pragma omp parallel
	{
		uint64 i, id, totThread;
		double x;
		double sumAll = 0;

		totThread = omp_get_num_threads();
		id = omp_get_thread_num();

		for (i = id; i < numSteps; i += totThread) 
		{
			x = (i + 0.5) * step;
			sumAll += 4.0 / (1.0 + x*x);
		}
#pragma omp atomic
		pi_val += sumAll * step;

	}

	double e_time = omp_get_wtime();

	typedef std::numeric_limits< double > dbl;
	cout.precision(dbl::max_digits10);

	std::cout << pi_val << " calculated in " << e_time - s_time;
}

/**
*  omp critical -> execute by one thread at a time
*  omp single   -> execute by any one thread
*  omp master   -> execute by the master thread (id == 0)
*/
// https://github.com/ilyak/openmp-tutorial/blob/master/09-single-master-critical.cpp
void single_master_critical()
{
#pragma omp parallel num_threads(8)
	{
		// mandled cout
		std::cout << "Hello from thread " << omp_get_thread_num() << " of " << omp_get_num_threads() << std::endl;

#pragma omp barrier // stop this madnes

#pragma omp critical // will bring justice
		std::cout << "<critical> Hello from thread " << omp_get_thread_num() << " of " << omp_get_num_threads() << std::endl;

#pragma omp barrier 

#pragma omp single
		std::cout << "<single> Hello from thread " << omp_get_thread_num() << " of " << omp_get_num_threads() << std::endl;
#pragma omp master
		std::cout << "<master> Hello from thread " << omp_get_thread_num() << " of " << omp_get_num_threads() << std::endl;
	}

}