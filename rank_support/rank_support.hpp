#include <iostream>
#include "../bit_vector.hpp"
#include <bits/stdc++.h>

using namespace std;
using namespace boost;


// get ceil(log2(x))
uint64_t get_log(uint64_t x)
{
	x--;
	uint64_t res = 0;
	while(x >>= 1) 
		res++;
	return res+1;
}

class rank_support
{
	public:
	bit_vector* b;
	vector <bit_vector> R1, R2;
	uint64_t sz1, sz2;
	uint64_t R1_bits, R2_bits;
	uint64_t R3_bits;

	bit_vector **R3; 

	rank_support(bit_vector *b) 
	{
		assert(b->size() >= 4);
		this->b = b;
		uint64_t log = get_log(b->size());
		sz1 = log*log/2;
		sz2 = log/2;
		assert(sz1%sz2 == 0);
		// could be better
		R1_bits = log+1;
		R2_bits = get_log(sz1)+1;

	
		uint64_t cnt1 = 0, cnt2 = 0;
		for (auto i = 0; i < b->size(); i++)
		{
			if (i%sz1 == 0)
			{
				R1.push_back(bit_vector(R1_bits, cnt1));	
				cnt2 = 0;
			}
			if (i%sz2 == 0)
				R2.push_back(bit_vector(R2_bits, cnt2));	
			if ((*b)[i])
			{
				cnt1++;
				cnt2++;
			}
		}

		R3_bits = get_log(sz2)+1;

		R3 = new bit_vector*[1<<sz2];
		for (uint64_t i = 0; i < (1<<sz2); i++)
		{
			R3[i] = new bit_vector[sz2];
			uint64_t x = i;
			uint64_t cnt = 0;
			for (int j = 0; j < sz2; j++)
			{
				cnt += x%2;
				R3[i][j] = bit_vector(R3_bits, cnt);
				x >>= 1;
			}
		}

	}

	uint64_t rank1(uint64_t i)
	{
		uint64_t s = (i/sz2)*sz2;
		uint64_t ind = 0;
		uint64_t mask = 1;
		for (uint64_t i = s; i < s+sz2; i++)
		{
			if ((*b)[i])
				ind += mask;
			mask <<= 1;
		}
			
		/*
		cerr << "R1: " << R1[i/sz1].to_ulong() << endl;
		cerr << "R2: " << R2[i/sz2].to_ulong() << endl;
		cerr << "R3 " << ind << ": "<< R3[ind][i%sz2].to_ulong() << endl;
		*/
		return R1[i/sz1].to_ulong() + R2[i/sz2].to_ulong() + R3[ind][i%sz2].to_ulong();
	}
	uint64_t rank0(uint64_t i)
	{
		return i - rank1(i);
	}

	uint64_t overhead()
	{
		uint64_t sum = 0;
		sum += R1.size()*(R1_bits-1);
		sum += R2.size()*(R2_bits-1);
		sum += (1<<sz2)*sz2*(R3_bits-1);
		return sum;
	}


	void print()
	{
		cerr << "bit_vector:\n" << (*b) << endl;
		cerr << "R1, sz1= " << sz1 << endl;
		for (auto x : R1)
			cerr << x.to_ulong() << " ";
		cerr << endl;
		cerr << "R2, sz2= " << sz2 << endl;
		for (auto x : R2)
			cerr << x.to_ulong() << " "; 
		cerr << endl;

	}
	void print_sizes()
	{
		cerr << "R1: " << sz1 << ", " << R1_bits << " R1 size: " << R1.size() << endl;
		cerr << "R2: " << sz2 << ", " << R2_bits << " R2 size: " << R2.size() << endl;
		cerr << "R3: " << (1<<sz2)<< " " << sz2  << ", " << R3_bits << endl;
	}



	bool test()
	{
		int cnt = 0;
		for (auto i = 0; i < b->size(); i++)
		{
			cnt += (*b)[i];
			if (cnt != rank1(i))
			{
				cerr << "test fail on index: " << i << endl;
				return false;
			}

		}
		cerr << "test passed" << endl;
		return true;
	}
	

};


