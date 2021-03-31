#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX = 505;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int N, M, A, B;
vector<int> adj[MAX];
vector<bool> visited;
vector<int> tin, low;
int timer;

bool dfs(int v, int rmp, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children = 0;
    for (int i = 0; i < adj[v].size(); ++i) {
        int to = adj[v][i];
        if (to == p || to == rmp) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            if (!dfs(to, rmp, v)) return false;
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p != -1) return false;
            ++children;
        }
    }
    if (p == -1 && children > 1) return false;
    return true;
}

int main() {
    while (scanf("%d%d", &N, &M) != EOF && N) {
        for (int i = 0; i < N; ++i) adj[i].clear();
        for (int i = 0; i < M; ++i) {
            scanf("%d%d", &A, &B);
            adj[A].push_back(B);
            adj[B].push_back(A);
        }
        bool canform = true;
        for (int i = 0; i < N; ++i) {
            timer = 0;
            visited.assign(N, false);
            tin.assign(N, -1);
            low.assign(N, -1);
            if (!dfs(!i, i)) {
                canform = false;
                break;
            }
            for (int j = 0; j < N; ++j) {
                if (j != i && tin[j] == -1) {
                    canform = false;
                    break;
                }
            }
            if (!canform) break;
        }
        printf("%s\n", canform ? "YES" : "NO");
    }

    return 0;
}