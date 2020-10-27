#include <iostream>
#include "select_support.hpp"

using namespace std;

int main()
{
	// example in slide
	/*
	string bit_string = "1001011101001010";
	reverse(bit_string.begin(), bit_string.end());
	bit_vector b(bit_string);
	rank_support r(&b);
	select_support s(&r);
	s.test();
	*/
	
	
	/*
	int len; cin >> len;
	bit_vector b = rand_bitvector(len);
	rank_support r(&b);
	cerr << "bit vector: " << b.size() << endl;
	r.test();
	
	cerr << "overhead: " << r.overhead() << endl;
	r.print_sizes();
	*/
	
	

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
