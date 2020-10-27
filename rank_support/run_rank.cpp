#include <iostream>
#include "rank_support.hpp"

using namespace std;

int main()
{
	// example in slide
	/*
	string bit_string = "1001011101001010";
	reverse(bit_string.begin(), bit_string.end());
	bit_vector b(bit_string);
	rank_support r(&b);
	r.print();
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
