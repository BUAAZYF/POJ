#include <cctype>
#include <cstdio>
#include <iostream>
#include <set>
#include <string>

using namespace std;

const int MAX = 22;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int t, K, E, mostcnt, curcnt;
set<string> keywords;
string cur, sentences[MAX];
int cnt[MAX];

int main() {
    freopen("in.txt", "r", stdin);
    t = 1;
    while (scanf("%d%d\n", &K, &E) != EOF) {
        keywords.clear();
        for (int i = 0; i < K; ++i) {
            cin >> cur;
            keywords.insert(cur);
        }
        getchar();
        mostcnt = 0;
        for (int i = 0; i < E; ++i) {
            getline(cin, sentences[i]);
            cur = "";
            curcnt = 0;
            for (int k = 0; k < sentences[i].size(); ++k) {
                if (isalpha(sentences[i][k]))
                    cur += tolower(sentences[i][k]);
                else {
                    if (!cur.empty() && keywords.find(cur) != keywords.end()) ++curcnt;
                    cur = "";
                }
            }
            cnt[i] = curcnt;
            mostcnt = max(mostcnt, curcnt);
        }
        cout << "Excuse Set #" << t++ << endl;
        for (int i = 0; i < E; ++i)
            if (cnt[i] == mostcnt) cout << sentences[i] << endl;
        cout << endl;
    }

    return 0;
}