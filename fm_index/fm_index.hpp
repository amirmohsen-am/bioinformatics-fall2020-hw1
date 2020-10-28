#include "../rank_support/rank_support.hpp"
#include <unordered_map>
#include <algorithm>
#include <sdsl/suffix_arrays.hpp>

using namespace std;

class fm_index
{
	public:
	uint64_t sigma;
	uint64_t size;
	rank_support* rank;
	string bwt;
	unordered_map <char, uint64_t> map;
	uint64_t* first;

	string input;

	void init(string input)
	{
		this->input = input;
		sdsl::csa_wt<> csa;
		sdsl::construct_im(csa, input, 1);
		sigma = csa.sigma;
		size = input.size();
		bwt = "";
		for (auto c: csa.bwt)
		{
			bwt += c ? c : '$';
		}

		rank = new rank_support [sigma];
		first = new uint64_t [sigma];

		vector <char> char_sorted;

		uint64_t cnt[sigma];
		for (auto c: input)
		{
			if (map.find(c) == map.end())
			{
				uint64_t tmp = map.size();
				map[c] = tmp;
				cnt[map[c]] = 0;
				char_sorted.push_back(c);
			}
			cnt[map[c]]++;
		}
		sort(char_sorted.begin(), char_sorted.end());
		uint64_t sum = 1; //because of $ at the begin
		for (auto c: char_sorted) 
		{
			first[map[c]] = sum; 
			sum += cnt[map[c]];
		}
		bit_vector* b = new bit_vector[size];
		for (auto c: char_sorted) 
			b[map[c]] = bit_vector(bwt.size());
		for (uint64_t i = 0; i < bwt.size(); i++)
		{
			char c = bwt[i];
			if (c != '$')
				b[map[c]][i] = 1;
		}
		for (auto c: char_sorted) 
			rank[map[c]] = rank_support(&b[map[c]]);
	}

	pair<uint64_t, uint64_t> query(string q)
	{
		uint64_t s = 0, e = bwt.size();
		for (auto it = q.rbegin(); it != q.rend(); it++)
		{
			char c = (*it);
			uint64_t ind = map[c];
			uint64_t l, r;
			if (s == 0)
				l = 0;
			else
				l = rank[ind].rank1(s-1);
			r = rank[ind].rank1(e-1);
			s = first[ind]+l;
			e = first[ind]+r; 
//			cerr << first[ind] << endl;
//			cerr << s << " " << e << endl;
		}
		return {s, e};
	}

	void print()
	{
		cerr << sigma << endl;
		cerr << size << endl;
		cerr << input << endl;
		cerr << bwt << endl;
		for (auto i: map)
		{
			char c = i.first;
			cerr << c << "," << i.second << ": " << (*rank[map[c]].b) << endl;
		}
		for (auto i: map)
		{
			char c = i.first;
			cerr << c << ": " << first[map[c]] << endl;
		}
	}
};
