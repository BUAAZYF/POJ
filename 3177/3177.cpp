#include <cstdio>
#include <cstring>
#include <set>
#include <vector>

using namespace std;

const int MAXF = 5005;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int F, R, x, y, cnt, ans, gcnt;
set<int> edges[MAXF];
bool visited[MAXF];
int tin[MAXF], low[MAXF];
vector<int> bridge;
int bridge_vertex[MAXF];
int group[MAXF];

void dfs(int prev, int cur) {
    visited[cur] = true;
    tin[cur] = low[cur] = cnt++;
    for (set<int>::iterator it = edges[cur].begin(); it != edges[cur].end(); ++it) {
        if (*it == prev) continue;
        if (visited[*it]) low[cur] = min(low[cur], tin[*it]);
        else {
            dfs(cur, *it);
            low[cur] = min(low[cur], low[*it]);
            if (low[*it] > tin[cur]) {
                bridge.push_back(*it);
                bridge.push_back(cur);
            }
        }
    }
}

void form_group(int v) {
    group[v] = gcnt;
    for (set<int>::iterator it = edges[v].begin(); it != edges[v].end(); ++it)
        if (group[*it] == 0) form_group(*it);
}

int main() {
    scanf("%d%d", &F, &R);
    for (int i = 1; i <= F; ++i) edges[i].clear();
    for (int i = 0; i < R; ++i) {
        scanf("%d%d", &x, &y);
        edges[x].insert(y);
        edges[y].insert(x);
    }
    cnt = 1;
    dfs(1, 1);
    for (int i = 0; i < bridge.size() / 2; ++i) {
        edges[bridge[2 * i]].erase(bridge[2 * i + 1]);
        edges[bridge[2 * i + 1]].erase(bridge[2 * i]);
    }
    gcnt = 1;
    for (int i = 1; i <= F; ++i) {
        if (group[i] == 0) {
            form_group(i);
            ++gcnt;
        }
    }
    ans = 0;
    for (int i = 0; i < bridge.size() / 2; ++i) {
        ++bridge_vertex[group[bridge[2 * i]]];
        ++bridge_vertex[group[bridge[2 * i + 1]]];
    }
    for (int i = 1; i < gcnt; ++i)
        if (bridge_vertex[i] == 1) ++ans;
    printf("%d\n", (ans + 1) / 2);

    return 0;
}