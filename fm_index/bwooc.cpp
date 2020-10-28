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
	}
	else if (type == "query")
	{
		string fm_file = argv[2];
		string query = argv[3];
	}
	else
		cerr << "wrong parameter" << endl;
	return 0;
}
