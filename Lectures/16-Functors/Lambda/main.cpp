#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>

using namespace std;
typedef pair<string, string> entry;

multimap<string, string> buildWordFamilies(const set<string>& words, char guess) {
   multimap<string, string> families;
   transform(words.begin(), words.end(), inserter(families, families.begin()), [guess](const string& word) {
      string family;
      for (size_t i = 0; i < word.length(); i++){
          if (word[i] == guess){
              family += guess;
          }
          else {
              family += "-";
          }
      } 
      return make_pair(family, word);
    });
    return families;
}

set<string> selectBiggestWordFamily(const multimap<string, string>& wordFamilies) {
    cout << wordFamilies.size() << endl;
    string biggest = max_element(wordFamilies.begin(), wordFamilies.end(), [&wordFamilies](const entry& lhs, const entry& rhs) {
        return wordFamilies.count(lhs.first) < wordFamilies.count(rhs.first);
    })->first;
    set<string> fam;
    for (auto itr = wordFamilies.equal_range(biggest).first; itr != wordFamilies.equal_range(biggest).second; ++itr) {
      fam.insert(itr->second);
    }
    return fam;
}

int main() {
    ifstream infile("dictionary.txt");
    set<string> dictionary;
    copy_if(istream_iterator<string>(infile), istream_iterator<string>(), inserter(dictionary, dictionary.end()), [](const string& value){return value.size() == 5;});
    cout << "read dictionary of size " << dictionary.size() << endl;
    set<string> newFamily = selectBiggestWordFamily(buildWordFamilies(dictionary, 'e'));
    cout << "biggest family for guess e contains " << *newFamily.begin() << " and is of size " << newFamily.size() << endl;
    return 0;
}
