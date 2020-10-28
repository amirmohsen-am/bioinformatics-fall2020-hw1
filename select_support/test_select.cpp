#include <iostream>
#include "select_support.hpp"

using namespace std;

int main()
{
	// example in slide
	/*
	bit_vector b = {1,0,0,1,0,1,1,1,0,1,0,0,1,0,1,0};
	rank_support r(&b);
	select_support s(&r);
	s.test();
	*/
	
	
	int len; cin >> len;
	bit_vector b = rand_bitvector(len);
	rank_support r(&b);
	cerr << "bit vector: " << b.size() << endl;
	r.test();
	
	cerr << "overhead: " << r.overhead() << endl;
	r.print_sizes();
	
	

	/*
	while(true)
	{
		uint64_t index;
		cin >> index;
		cout << r.rank1(index) << endl;
	}
	*/

	
	return 0;
}
