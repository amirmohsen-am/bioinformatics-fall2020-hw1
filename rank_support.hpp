#include <iostream>
#include "boost/dynamic_bitset.hpp"
#include <bits/stdc++.h>

using namespace std;
using namespace boost;

class bit_vector : public dynamic_bitset<>
{
	// include the constructors
	using dynamic_bitset::dynamic_bitset;

	public:

	void save(ofstream& fout)
	{
	
		uint64_t output_size = ((this->size() + 7) / 8)*8;
		//fout << output_size << "\n";
		fout.write((char*)&output_size, sizeof(output_size));
		// from stackoverflow
		bit_vector x = (*this);
		// TODO optimize
		auto ulong_mask = bit_vector(this->size(), 0xFFul);
		uint64_t cnt = 0;
		for (auto i = 0; i < this->size()/8; i++) {
			uint8_t byte = (x & ulong_mask).to_ulong();
			fout.write(reinterpret_cast<char*>(&byte), 1);

			x >>= 8;
			cnt += 8;
		}
//		cerr << cnt << " " << output_size << endl;
//		cerr << this->size() << endl;
		assert(cnt == output_size);
	}
	void load(ifstream& fin)
	{
		this->clear();
		uint64_t sz = 0;
		fin.read((char*)&sz, sizeof(sz));
		cerr << sz << endl;
		cerr << sizeof(sz) << endl;
		this->resize(sz);
		for (auto i = 0; i < this->size()/8; i++) 
		{
			char byte;
			fin.read(&byte, 1);
			for (int j = 0; j < 8; j++)
			{
				(*this)[i*8+j] = byte&1;
				byte >>= 1;
			}
		}
	}


};

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


	void init()
	{
		
	}


	

};

bool test(rank_support r)
{
	int cnt = 0;
	for (auto i = 0; i < r.b->size(); i++)
	{
		cnt += (*r.b)[i];
		int rank = r.rank1(i);
		if (cnt != rank)
		{
			cerr << "test fail on index: " << i << endl;
			return false;
		}

	}
	cerr << "test passed" << endl;
	return true;
}


bit_vector rand_bitvector(uint64_t sz) 
{
	bit_vector res(sz);
	for (auto i = 0; i < sz; i++)
		res[i] = rand()%2;
	return res;
}

int main()
{
	/*
	bit_vector t(1<<28);
	t.set(1<<27, 1);
	int cnt = 0;
	for (int i = 0; i < 1000; i++)
	{
		cerr << i << endl;
		cnt += (t >> 1)[(1<<27)-1];
	}
	cerr << cnt << endl;
	*/
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
	test(r);
	
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
