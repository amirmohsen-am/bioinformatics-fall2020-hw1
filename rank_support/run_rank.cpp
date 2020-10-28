#include <iostream>
#include "rank_support.hpp"

using namespace std;

int main()
{
	// example in slide
	/*
	bit_vector b = {1,0,0,1,0,1,1,1,0,1,0,0,1,0,1,0};
	rank_support r(&b);
	r.print();
	*/
	
	int len; cin >> len;
	bit_vector b = rand_bitvector(len);
	rank_support r1(&b);
	r1.print();

	r1.test();
	
	cerr << "overhead: " << r1.overhead() << endl;
	r1.print_sizes();


	// Save and load test
	ofstream fout("test.txt");
	r1.save(fout);
	fout.close();

	ifstream fin("test.txt");
	rank_support r2;
	r2.load(fin);

	cerr << (*r2.b) << endl;
	r2.print();

	r2.test();

	cerr << "overhead: " << r2.overhead() << endl;
	r2.print_sizes();

	
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
