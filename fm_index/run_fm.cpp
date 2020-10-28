#include "fm_index.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	string input = "abaaba"; 
	fm_index fm1;
	fm1.init(input);
	fm1.print();

	ofstream fout("test.txt");
	fm1.save(fout);
	fout.close();


	fm_index fm2;
	ifstream fin("test.txt");
	fm2.load(fin);
	fin.close();

	fm2.print();
	
	/*

	while(true)
	{
		string q;
		cin >> q;
		auto res = fm1.query(q);
		cout << res.first << " " << res.second << endl;
	}
	*/
	return 0;
}

