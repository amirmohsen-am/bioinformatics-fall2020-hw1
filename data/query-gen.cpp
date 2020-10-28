#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "provide parameters" << endl;
		return 0;
	}

	string type = argv[1];
	char alpha[] = {'A', 'C', 'T', 'G'};
	if (type == "random")
	{
		int len = atoi(argv[2]); 
		int num = atoi(argv[3]);
		while(num--)
		{
			string res = "";
			for (int i = 0; i < len; i++)
				res += alpha[rand()%4];
			cout << res << "\n";
		}
	}
	else
	{
		int len = atoi(argv[2]); 
		int num = atoi(argv[3]);
		string fname = argv[4];
		ifstream fin(fname);
		string input = "";
		string s;
		while (fin >> s)
			input += s;
		while(num--)
		{
			string sub = input.substr(rand()%input.size(), len); 
			cout << sub << "\n";
		}
	}
}
