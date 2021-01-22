#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <string>

using namespace std;

const int MAX = 27;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

char a, b;
int to[MAX];
set<int> nodes, from[MAX];
string buffer;

void dfs(string s) {
    if (s.size() == nodes.size()) {
        printf("%s\n", s.c_str());
        return;
    }
    for (set<int>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
        if (to[*it] == 0) {
            for (set<int>::iterator nt = from[*it].begin(); nt != from[*it].end(); ++nt) --to[*nt];
            to[*it] = -1;
            dfs(s + char('a' + *it));
            to[*it] = 0;
            for (set<int>::iterator nt = from[*it].begin(); nt != from[*it].end(); ++nt) ++to[*nt];
        }
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    while (getline(cin, buffer)) {
        nodes.clear();
        memset(to, 0, sizeof(to));
        for (int i = 0; i < buffer.size(); ++i) {
            if (islower(buffer[i])) {
                from[buffer[i] - 'a'].clear();
                nodes.insert(buffer[i] - 'a');
            }
        }
        getline(cin, buffer);
        int cnt = 0;
        for (int i = 0; i < buffer.size(); ++i)
            if (islower(buffer[i])) buffer[cnt++] = buffer[i];
        for (int i = 0; i < cnt; i += 2) {
            a = buffer[i], b = buffer[i + 1];
            set<int>& fa = from[a - 'a'];
            if (fa.find(b - 'a') == fa.end()) {
                fa.insert(b - 'a');
                ++to[b - 'a'];
            }
        }
        string s = "";
        dfs(s);
        putchar('\n');
    }

    return 0;
}