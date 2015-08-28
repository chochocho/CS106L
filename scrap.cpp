#include <iostream>
#include <fstream>
#include <ctime>
#include <map>
#include <cstdlib>
using namespace std;

int main() {
	map<string, int> numberMap;
	numberMap["zero"] = 0;
	numberMap["one"] = 1;
	numberMap["two"] = 2;
	for (map<string, int>::iterator itr = numberMap.begin(); itr != numberMap.end(); ++itr) {
		cout << itr->first << ": " << itr->second << endl;
	}
};

// int main () {
// 	string str = "dogpilechicken";
// 	string maskedstr = str;
// 	char c = 'e';
// 	for (int i = 0; i < maskedstr.length(); i++) {
// 		if (maskedstr[i] != c) {
// 			maskedstr[i] = '_';
// 		}
// 	}
// 	cout << maskedstr << endl;
// 	cout << str << endl;
// };

// void readFile(ifstream &inFile) {
// 	int count;
// 	int node1;
// 	int node2;
// 	inFile >> count;
// 	cout << count << endl;
// 	while(!inFile.eof()) {
// 		inFile >> node1 >> node2;
// 		cout << node1 << " "  << node2 << endl;
// 	}
// }

// int main() {
//     char filename[255];
//     cout << "Please enter a filename: ";
//     cin >> filename;

// 	ifstream inFile;
//     inFile.open(filename);
// 	readFile(inFile);
// 	inFile.close();
// 	return 0;
// }

// // reads text dictionry and fills up table based on first letter
// int main() {
// 	vector< vector<string> > table;
// 	table.resize(26);
// 	ifstream inFile("dictionary.txt");
//     string word;
// 	int count = 0;
// 	while(!inFile.eof()) {
// 		inFile >> word;
// 		// table[word.length()].push_back(word);
// 		// cout << word << endl;
// 		// cout << word[0] << endl;
// 		// cout << word[0] - 97 << endl;
// 		table[word[0] - 97].push_back(word);
// 		count++;
// 	};
// 	for (int i = 0; i < table[0].size(); i++) {
// 		cout << table[0][i] << endl;
// 	}
// 	inFile.close();
// };
