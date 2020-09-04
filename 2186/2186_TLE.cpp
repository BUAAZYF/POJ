#include <algorithm>
#include <cstdio>
#include <set>
#include <bitset>

using namespace std;

const int MAX = 10005;

int N, M, A, B, ans;
set<int> edges[MAX];
bitset<MAX> dp[MAX];

void init() {
    for (int i = 1; i <= N; ++i) {
        edges[i].clear();
        dp[i].reset();
    }
}

void dfs(int root, int node) {
    if (dp[root].test(node)) {
        dp[root] |= dp[node];
        return;
    }
    dp[root].set(node, true);
    for (set<int>::iterator it = edges[node].begin(); it != edges[node].end(); ++it) 
        dfs(root, *it);
}
    

int main() {
    while (scanf("%d%d", &N, &M) != EOF) {
    init();
    while (M--) {
        scanf("%d%d", &A, &B);
        edges[B].insert(A);
    }
    for (int i = 1;i <= N; ++i) {
        if (!dp[i].test(i)) dfs(i, i);
    }
    ans = 0;
    bitset<MAX> full;
    for (int i = 1; i <= N; ++i) full.set(i, true);
    for (int i = 1; i <= N; ++i) {
        if (dp[i] == full) ++ans;
    }
    printf("%d\n", ans);
    }

    return 0;
}