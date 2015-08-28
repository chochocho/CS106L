#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
using namespace std;

void loadDictionary(vector<string>& v, int length);
void removeWords(vector<string>& v, char c);
void updateHidden(string&, string);

string maskString(string str, char c);
string createFamilies(vector<string>& v, char c);

int main() {

	vector<string> wordList;

	// asks user for a word length
	int wordLength;
	cout << "Enter word length: ";

    while (true) {
    	cin >> wordLength;
    	if (cin.fail() || wordLength < 0) {
    		cin.clear();
    		cin.ignore(999, '\n');
    		cout << "Invalid input. Please try again: ";
    		continue;
    	};
    	loadDictionary(wordList, wordLength);
    	if (!wordList.empty()) break;
    	cout << "No words of length " << wordLength << ". Enter another length: ";
    }

    // prints out list of words for error checking
	// for (vector<string>::iterator itr = wordList.begin(); itr != wordList.end(); ++itr) {
	// 	cout << *itr << endl;
	// }

	// asks user for a guess amount
	int guessMax;
	cout << "Enter number of guesses: ";
	
	while (true) {
		cin >> guessMax;
		if (cin.fail() || guessMax < 0) {
			cin.clear();
			cin.ignore(999, '\n');
			cout << "Invalid input. Please try again: ";
			continue;
		};
		if (guessMax > 0) break;
    }

    // plays the game
    set<char> guessList;
	string hiddenWord(wordLength, '_');

	while (guessList.size() < guessMax) {
		cout << hiddenWord << ", " << guessMax - guessList.size() << " guesses remaining." << endl;

		if (guessList.size() > 0) {
			cout << "Previous guesses: ";
			for (set<char>::iterator itr = guessList.begin(); itr != guessList.end(); ++itr) {
				cout << *itr << " ";
			}
			cout << " " << endl;	
		}

		char guess;
		cout << "Make a guess: ";
		cin >> guess;
		if (!isalpha(guess)) {
			cout << "Invalid guess. Try again." << endl;
		} else if (guessList.count(guess)) {
			cout << "You already guessed this. Make another guess." << endl;
		} else {
			updateHidden(hiddenWord, createFamilies(wordList, guess));
			guessList.insert(guess);	
		}
		
		if (hiddenWord.find('_') == string::npos) {
			cout << "YOU WIN!" << endl;
			break;
		}
	}
	
	if (hiddenWord.find('_') != string::npos) {
		cout << "YOU LOSE!" << endl;
	}
	// for (vector<string>::iterator itr = wordList.begin(); itr != wordList.end(); ++itr) {
	// 	cout << *itr << endl;
	// }
};

// loads wordList
void loadDictionary(vector<string>& list, int wordLength) {
	string word;
	ifstream inFile("dictionary.txt");
	while(!inFile.eof()) {
		inFile >> word;
		if (word.length() == wordLength) {
			list.push_back(word);
		}
	};
	inFile.close();
}

// note: when iterating with erase(), increment only for elements that aren't removed.
void removeWords(vector<string>& v, char c) {
	int i = 0;
	while (i < v.size()) {
		if (v[i].find(c) != string::npos) {
			v.erase(v.begin() + i);
		} else {
			i++;
		}
	}
}

void updateHidden(string& original, string update) {
	for (int i = 0; i < original.size(); i++) {
		if (original[i] == '_') {
			original[i] = update[i];
		}
	}
}

// masks a string to determine its family
string maskString(string str, char c) {
	string maskedStr = str;
	for (size_t i = 0; i < maskedStr.size(); i++) {
		if (maskedStr[i] != c) {
			maskedStr[i] = '_';
		}
	}
	return maskedStr;
}

// creates families and checks for the greatest
string createFamilies(vector<string>& v, char c) {
	map<string, int> wordFamilies;
	int maxValue = 0;
	string maxKey;

	// generate the families
	for (vector<string>::iterator itr = v.begin(); itr != v.end(); ++itr) {
		string maskedStr = maskString(*itr, c);
		if (wordFamilies.count(maskedStr)) {
			wordFamilies[maskedStr]++;
		} else {
			wordFamilies[maskedStr] = 1;
		}
		if (wordFamilies[maskedStr] > maxValue) {
			maxKey = maskedStr;
			maxValue = wordFamilies[maskedStr];
		};
	}
	// for (map<string, int>::iterator itr = wordFamilies.begin(); itr != wordFamilies.end(); ++itr) {
	// 	cout << itr->first << ": " << itr->second << endl;
	// }

	// identifies which family has the most members
	// for (map<string, int>::iterator itr = wordFamilies.begin(); itr != wordFamilies.end(); ++itr) {
	// 	if (itr->second > maxValue) {
	// 		maxKey = itr->first;
	// 		maxValue = itr->second;
	// 	}
	// }
	// cout << maxKey << ": " << maxValue << endl;

	// removes all words from other families
	int i = 0;
	while (i < v.size()) {
		if (maskString(v[i], c) != maxKey) {
			v.erase(v.begin() + i);
		} else {
			i++;
		}
	}
	return maxKey;
}

