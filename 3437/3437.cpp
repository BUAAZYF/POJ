#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> Pr;

const int MAX = 10005;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int t, sh, dh, cnt;
string s;
Pr nodes[MAX];
int parents[MAX];
vector<int> stk;

void dfs(int idx, int par, int height) {
    if (idx == s.size()) return;
    if (s[idx] == 'd') {
        int pre_sliber = -1;
        for (int i = stk.size() - 1; i >= 0; --i) {
            if (nodes[stk[i]].first == height + 1) {
                pre_sliber = i;
                break;
            }
        }
        parents[cnt] = par;
        stk.push_back(cnt);
        if (pre_sliber != -1) nodes[cnt++] = Pr(height + 1, nodes[stk[pre_sliber]].second + 1);
        else nodes[cnt++] = Pr(height + 1, nodes[par].second + 1);
        sh = max(sh, height + 1);
        dh = max(dh, nodes[cnt - 1].second);
        dfs(idx + 1, cnt - 1, height + 1);
    } else {
        while (!stk.empty() && stk[stk.size() - 1] != par) stk.erase(stk.begin() + stk.size() - 1);
        dfs(idx + 1, parents[par], height - 1);
    }
}

int main() {
    t = 1;
    while (cin >> s && s != "#") {
        sh = dh = cnt = 0;
        stk.clear();
        nodes[cnt++] = Pr(0, 0);
        dfs(0, 0, 0);
        printf("Tree %d: %d => %d\n", t++, sh, dh);
    }

    return 0;
}