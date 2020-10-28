#include <iostream>
#include "select_support.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	// example in slide
	/*
	bit_vector b = {1,0,0,1,0,1,1,1,0,1,0,0,1,0,1,0};
	rank_support r(&b);
	r.print();
	*/
	if (argc < 2)
	{
		cout << "Usage: provide parameters" << endl;
		return 0;
	}


	uint64_t len = atoi(argv[1]);
	bit_vector b = rand_bitvector(len);
	rank_support r1(&b);
	select_support s(&r1);

	uint64_t sum = 0;
	for (int i = 0; i < 1000*1000; i++)
		sum += s.select1(rand()% r1.b->size());
	cout << sum << endl;

//	r1.print();

//	r1.test();
	
//	cerr << "overhead: " << r1.overhead() << endl;
//	r1.print_sizes();

	
	return 0;
}
