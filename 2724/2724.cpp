#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int MAX = 1050;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int N, M, V;
string s;
vector<int> graph[2 * MAX];
int matched[2 * MAX];
bool used[2 * MAX];
set<string> vertex;
vector<string> vc;

int caldis(string& s1, string& s2) {
    int cnt = 0;
    for (int i = 0; i < s1.size(); ++i)
        if (s1[i] != s2[i]) ++cnt;
    return cnt;
}

void add_edge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

bool dfs(int v) {
    used[v] = true;
    for (int i = 0; i < graph[v].size(); ++i) {
        int u = graph[v][i], w = matched[u];
        if (w < 0 || !used[w] && dfs(w)) {
            matched[v] = u;
            matched[u] = v;
            return true;
        }
    }
    return false;
}

int bipartite_matching() {
    int ans = 0;
    memset(matched, -1, sizeof(matched));
    for (int v = 0; v < V; ++v) {
        if (matched[v] >= 0) continue;
        memset(used, false, sizeof(used));
        if (dfs(v)) ++ans;
    }
    return ans;
}

int main() {
    while (scanf("%d%d\n", &N, &M) != EOF && N) {
        vertex.clear();
        for (int i = 0; i < M; ++i) {
            getline(cin, s);
            string::iterator pos = find(s.begin(), s.end(), '*');
            if (pos == s.end())
                vertex.insert(s);
            else {
                *pos = '0', vertex.insert(s);
                *pos = '1', vertex.insert(s);
            }
        }
        vc.clear();
        for (set<string>::iterator it = vertex.begin(); it != vertex.end(); ++it) vc.push_back(*it);
        V = vc.size();
        for (int i = 0; i < V; ++i) graph[i].clear();
        for (int i = 0; i < V; ++i)
            for (int j = i + 1; j < V; ++j)
                if (caldis(vc[i], vc[j]) == 1) add_edge(i, j);

        printf("%d\n", V - bipartite_matching());
    }

    return 0;
}