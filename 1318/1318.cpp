#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

const string STOP = "XXXXXX";
const string SEP = "******";

string cur, srt;
map<string, set<string> > words;

int main() {
    while (cin >> cur && cur != STOP) {
        srt = cur;
        sort(srt.begin(), srt.end());
        if (words.find(srt) == words.end()) words[srt] = set<string>();
        words[srt].insert(cur);
    }
    while (cin >> cur && cur != STOP) {
        srt = cur;
        sort(srt.begin(), srt.end());
        if (words.find(srt) == words.end())
            cout << "NOT A VALID WORD" << endl;
        else {
            for (set<string>::iterator it = words[srt].begin(); it != words[srt].end(); ++it)
                cout << *it << endl;
        }
        cout << SEP << endl;
    }

    return 0;
}