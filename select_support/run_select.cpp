#include <iostream>
#include "select_support.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	// example in slide
	// 1001011101001010
	/*
	bit_vector b = {1,0,0,1,0,1,1,1,0,1,0,0,1,0,1,0};
	rank_support r(&b);
	r.print();
	*/

	string s;
	cin >> s;
	bit_vector b(s.size());
	for (int i = 0; i < s.size(); i++)
		b[i] = s[i]-'0';
	rank_support r1(&b);
	select_support s1(&r1);

	s1.test();

	cout << "overhead: " << r1.overhead() << endl;

	int ind;
	while (cin >> ind) 
	{
		cout << "select1(" << ind << ") = " << s1.select1(ind) << endl;
	}

//	r1.print();

//	r1.test();
	

	
	return 0;
}
