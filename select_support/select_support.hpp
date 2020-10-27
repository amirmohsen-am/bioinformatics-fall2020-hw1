#include <iostream>
#include "../rank_support/rank_support.hpp"

using namespace std;


class select_support
{
	public:
	rank_support* r;
	select_support(rank_support* r)
	{
		this->r = r;
	}

	uint64_t select(uint64_t i, bool bit)
	{
		if (i == 0) return -1;
		uint64_t s = -1, e = r->b->size();
		uint64_t mid;
		while (e - s > 1)
		{
			mid = (e+s)/2;
			if (r->rank(mid, bit) < i)
				s = mid;
			else
				e = mid;
		}
		return e == r->b->size() ? -1 : e;
	}
	uint64_t select1(uint64_t i)
	{
		return select(i, 1);	
	}
	uint64_t select0(uint64_t i)
	{
		return select(i, 0);	
	}

	uint64_t overhead()
	{
		return r->overhead();
	}

	bool test()
	{
		cerr << "testing select_support on bitvector size: " << r->b->size() << endl;
		int cnt = 0;
		for (auto i = 0; i < r->b->size(); i++)
		{
			if ((*r->b)[i])
			{
				cnt++;
				if (select1(cnt) != i)
				{
					cerr << "test fail on select1-" << cnt << endl;
					return false;
				}
			}
		}
		cerr << "test passed" << endl;
		return true;
	}
	

};


