#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string s, sorted;
map<string, vector<string> > groups;

bool cmp(const pair<int, string>& pr1, const pair<int, string>& pr2) {
    return pr1.first > pr2.first || pr1.first == pr2.first && groups[pr1.second][0] < groups[pr2.second][0];
}

int main() {
    vector<pair<int, string> > cnt;
    while (cin >> s) {
        sorted = s;
        sort(sorted.begin(), sorted.end());
        if (groups.find(sorted) == groups.end()) groups[sorted] = vector<string>();
        groups[sorted].push_back(s);
    }
    for (map<string, vector<string> >::iterator it = groups.begin(); it != groups.end(); ++it) {
        cnt.push_back(make_pair(it->second.size(), it->first));
        sort(it->second.begin(), it->second.end());
    }
    sort(cnt.begin(), cnt.end(), cmp);
    for (int i = 0; i < (5 >= cnt.size() ? cnt.size() : 5); ++i) {
        cout << "Group of size " << cnt[i].first << ": ";
        for (int j = 0; j < groups[cnt[i].second].size(); ++j) {
            if (j > 0 && groups[cnt[i].second][j] == groups[cnt[i].second][j - 1]) continue;
            cout << groups[cnt[i].second][j] << " ";
        }
        cout << ".\n";
    }

    return 0;
}