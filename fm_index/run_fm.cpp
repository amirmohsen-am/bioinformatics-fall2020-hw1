#include "fm_index.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	string input = "abaaba"; 
	fm_index fm;
	fm.init(input);
	fm.print();

	while(true)
	{
		string q;
		cin >> q;
		auto res = fm.query(q);
		cout << res.first << " " << res.second << endl;
	}
	return 0;
}

