#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string uppercasify(string _str)
{
  string str = "";

  for (char c : _str)
    str += toupper(c);

  return str;
}

int main()
{
  ifstream ifs("list.txt");

  string str;
  vector<string> words;
  vector<bool> noRepeats;

  while (ifs >> str) {
    words.push_back(uppercasify(str));
    noRepeats.push_back(str.size() == 7);
  }

  for (int s = 0; s < words.size(); s++)
    for (int i = 0; i < 7; i++)
      for (int j = 0; j < 7; j++)
        if (words[s][i] == words[s][j] && i != j)
          noRepeats[s] = false;

  ofstream ofs("7-list.txt");
  for (int i = 0; i < words.size(); i++)
    if (noRepeats[i])
      ofs << words[i] << endl;

  return 0;
}
