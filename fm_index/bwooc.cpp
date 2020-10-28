#include "fm_index.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "need 3 parameters" << endl;
		return 0;
	}
	string type = argv[1];
	
	if (type == "build")
	{
		string input = argv[2];
		string out_file = argv[3];
		ofstream fout(out_file);
		fm_index fm;
		fm.init(input);
		fm.save(fout);
		cout << fm.sigma << endl;
		cout << fm.size << endl;

//		fm.print();
	}
	else if (type == "build2")
	{
		string in_file = argv[2];
		string out_file = argv[3];
		ifstream fin(in_file);
		ofstream fout(out_file);

		string s;
		string input = "";
		while (fin >> s)
			input += s;

		fm_index fm;
		fm.init(input);
		fm.save(fout);
		cout << fm.sigma << endl;
		cout << fm.size << endl;

//		fm.print();
	}
	else if (type == "query")
	{
		string fm_file = argv[2];
		string query_file = argv[3];
		ifstream fin(fm_file);
		fm_index fm;
		fm.load(fin);
//		fm.print();

		ifstream qstream(query_file);
		string query;
		while (qstream >> query)
		{
			auto res = fm.query(query);
			cout << res.first << " " << res.second << "\n";
		}

	}
	else
		cerr << "wrong parameter" << endl;
	return 0;
}
