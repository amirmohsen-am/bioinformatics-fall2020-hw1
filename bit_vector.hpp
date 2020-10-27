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

bit_vector rand_bitvector(uint64_t sz) 
{
	bit_vector res(sz);
	for (auto i = 0; i < sz; i++)
		res[i] = rand()%2;
	return res;
}

